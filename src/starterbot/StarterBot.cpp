#include "StarterBot.h"
#include "Tools.h"
#include "MapTools.h"
#include <Blackboard.h>
#include <format>

#include "BT.h"
#include "selfmadeBT/selfmadeBT.h"
#include <OverlordUtils.h>
#include <ZerglingUtils.h>
#include <selfmadeBT/MutaliskUtils.h>

StarterBot::StarterBot()
{
    pData = new Blackboard(e_buildOrderType::FourPool);
    pData->currMinerals = 0;
    pData->currSupply = 0;
    pData->thresholdSupply = 0;

    pData->nWantedWorkersTotal = NWANTED_WORKERS_TOTAL;

    pBT = BT_Builder::buildMainBT(pData);
}

//functions needed for initialisating : 
void StarterBot::save_base_position() {
    //We look for a hatchery, and save its position. 
    BWAPI::Unit base = Tools::GetUnitOfType(BWAPI::UnitType(131));
    BWAPI::Position base_pos = base->getPosition();
    this->pData->ownedBases.push_back(OwnedBase(base_pos));

    BWAPI::TilePosition base_tile_pos = base->getTilePosition();
    this->pData->basePosition = base_pos;
    // TODO: check consistency, as position is supposed to be TilePosition * 32
    //       which doesn't seem to be the case here!
    if (base_tile_pos == BWAPI::TilePosition(31, 7)) {
		this->pData->enemyBasesPositions.push_back(BWAPI::Position(2112, 3824));
        //this->pData->naturalPosition = BWAPI::Position(992, 3472);
        //this->pData->enemyNaturalPosition = BWAPI::Position(2080, 656);
        this->pData->myPosIdx = 0;
        this->pData->enemyPosIdx= 1;
	}
	else { // base_tile_pos == BWAPI::TilePosition(64, 118)
		this->pData->enemyBasesPositions.push_back(BWAPI::Position(1056, 272));
        this->pData->myPosIdx = 1;
        this->pData->enemyPosIdx = 0;
	}
}
void StarterBot::create_minerals_table() {
    //function done by Matt, ask me i you have quesions.

    Blackboard* b = this->pData;
    std::vector<int> indx_to_ID;
    std::map<int, int> ID_to_indx;
    std::vector<int>mineralsOccupancyTable;

    BWAPI::Unitset myMinerals = BWAPI::Broodwar->getMinerals();
    BWAPI::Position base_pos = this->pData->basePosition;
    float r = 400;
    BWAPI::Unitset CANDIDATES;
    CANDIDATES = Tools::GetUnitsInRadius(base_pos, r, myMinerals);
    
    int count = 0;
    for (auto& u : CANDIDATES) {
        
        indx_to_ID.push_back(u->getID());
        ID_to_indx[count] = u->getID();
        mineralsOccupancyTable.push_back(0);
        count++;

    }
    this->pData->mineralsOccupancyTable = mineralsOccupancyTable;
    this->pData->minerals_ID_to_indx = ID_to_indx;
    this->pData->minerals_indx_to_ID = indx_to_ID;
}

// Called when the bot starts!
void StarterBot::onStart()
{
    // Set our BWAPI options here    
	BWAPI::Broodwar->setLocalSpeed(10);
    BWAPI::Broodwar->setFrameSkip(0);
    
    // Enable the flag that tells BWAPI top let users enter input while bot plays
    BWAPI::Broodwar->enableFlag(BWAPI::Flag::UserInput);

    // Call MapTools OnStart
    m_mapTools.onStart();

    //Bwem
    //BWEM::Map::Instance().Initialize(BWAPI::BroodwarPtr);
    this->save_base_position();
    this->create_minerals_table();

    BWAPI::UnitType typeA = BWAPI::UnitTypes::Terran_Marine;
    BWAPI::UnitType typeB = BWAPI::UnitTypes::Zerg_Zergling;
    

}

// Called on each frame of the game
void StarterBot::onFrame()
{
    // Update our MapTools information
    m_mapTools.onFrame();

    pData->buildOrder.evaluate(pData);

    pData->currMinerals = BWAPI::Broodwar->self()->minerals();
    pData->currSupply = Tools::GetUnusedSupply(true);

    std::vector<BWAPI::Unit> overlords;
    Tools::GetAllUnitsOfType(BWAPI::UnitTypes::Zerg_Overlord, overlords);
    pData->nbOverlords = overlords.size();

    pData->enemyRace = BWAPI::Broodwar->enemy()->getRace();
    
    // AI BT
    if (pBT != nullptr && pBT->Evaluate(pData) != BT_NODE::RUNNING)
    {
        std::cout << "end of BT execution" << std::endl;
        delete (BT_DECORATOR*)pBT;
        pBT = nullptr;
    }
    /*if (pBtTest != nullptr && pBtTest->Evaluate(pData) != BT_NODE::RUNNING)
    {
        std::cout << "end of BT_Test execution" << std::endl;
        delete (BT_DECORATOR*)pBtTest;
        pBtTest = nullptr;
    }*/

    // iterate over all units, those who don't yet have a BT will be assigned one
    BWAPI::Unitset allUnits = BWAPI::Broodwar->self()->getUnits();
    for (auto it = allUnits.begin(); it != allUnits.end(); ++it) {
        BWAPI::Unit unit = *it;
        if (unit == nullptr) continue; // the unit is null (should not happen)
        if (!unit->exists()) continue; // the unit does not exist (dead)
        if (m_unitBT.count(unit)) continue; // the unit already has a BT
        if (!unit->isCompleted()) continue; // the unit is not completed

        // TODO: if zerg egg is dying then cancel last sec
        if (unit->getType() == BWAPI::UnitTypes::Zerg_Egg) continue; // the unit is an egg, we will assign a BT once it is a true unit
        if (unit->getType() == BWAPI::UnitTypes::Zerg_Larva) continue; // the unit is a larva, we will assign a BT once it is a true unit

        // Handle Mutalisk Squad Insertion
        if (unit->getType() == BWAPI::UnitTypes::Zerg_Mutalisk) {
            // if there is a squad close by, join it
            bool foundASquad = false;
            for (const auto [squad, squadBT] : m_mutaliskSquadsBT) {
                if (squad->getPosition().getDistance(unit->getPosition()) < 100) {
                    squad->addUnit(unit);
                    foundASquad = true;
                    break;
                }
            }

            // If no squad was found, make a new one
            if (!foundASquad) {
                Squad* squad = new Squad();
                squad->addUnit(unit);

                m_mutaliskSquadsBT[squad] = MutaliskUtils::SquadTree(squad, nullptr);
            }
        }

        switch (unit->getType()) {
        case BWAPI::UnitTypes::Zerg_Overlord:
            m_unitBT.insert(std::make_pair(unit, OverlordUtils::CreateIndividualTree(unit)));
            break;

        case BWAPI::UnitTypes::Zerg_Zergling:
            m_unitBT.insert(std::make_pair(unit, ZerglingUtils::CreateTree(unit)));
            break;
        };
    }

    // iterate over all the BTs, those assigned to dead units can be removed
    for (const auto& [unit, unitBT] : m_unitBT) {
        if (unit->exists()) continue; // the unit is alive

		delete (BT_DECORATOR*)unitBT;

        m_unitBT.erase(unit);
    }

    // execute all BTs
    for (const auto& [unit, unitBT] : m_unitBT) {
        unitBT->Evaluate(pData);
        //unitBT->Reset();
    }

    // Draw unit health bars, which brood war unfortunately does not do
    Tools::DrawUnitHealthBars();

    // Draw some relevent information to the screen to help us debug the bot
    drawDebugInformation();
}

// Draw some relevent information to the screen to help us debug the bot
void StarterBot::drawDebugInformation()
{
    //std::string buildOrderStr = "Buildorder: " + std::to_string(pData->buildOrder.getCurrentIndex()) + "/" + std::to_string(pData->buildOrder.getSize());
    //BWAPI::Broodwar->drawTextScreen(BWAPI::Position(10, 10), buildOrderStr.c_str());
    std::string supplyUsedStr = "Supply: " + std::to_string(BWAPI::Broodwar->self()->supplyUsed()) + "/" + std::to_string(Tools::GetTotalSupply(true));
    BWAPI::Broodwar->drawTextScreen(BWAPI::Position(20, 10), supplyUsedStr.c_str());
    Tools::DrawUnitCommands();
    Tools::DrawUnitBoundingBoxes();
}

// Called whenever the game ends and tells you if you won or not
void StarterBot::onEnd(bool isWinner)
{
    std::cout << "We " << (isWinner ? "won!" : "lost!") << "\n";
}

// Called whenever a unit is destroyed, with a pointer to the unit
void StarterBot::onUnitDestroy(BWAPI::Unit unit)
{

}

// Called whenever a unit is morphed, with a pointer to the unit
// Zerg units morph when they turn into other units
void StarterBot::onUnitMorph(BWAPI::Unit unit)
{   
    if ((unit->getInitialType() == BWAPI::Broodwar->self()->getRace().getWorker()) && Tools::IsMine(unit)) {
        for (auto& base : this->pData->ownedBases) {
            base.freeWorker(unit);

        }
    }
}

// Called whenever a text is sent to the game by a user
void StarterBot::onSendText(std::string text) 
{ 
    if (text == "/map")
    {
        m_mapTools.toggleDraw();
    }
}

// Called whenever a unit is created, with a pointer to the destroyed unit
// Units are created in buildings like barracks before they are visible, 
// so this will trigger when you issue the build command for most units
void StarterBot::onUnitCreate(BWAPI::Unit unit)
{ 
	
}

// Called whenever a unit finished construction, with a pointer to the unit
void StarterBot::onUnitComplete(BWAPI::Unit unit)
{

    //if unit is worker : attach it to its base (the closest base)
    if (unit->getType() == BWAPI::Broodwar->self()->getRace().getWorker() && Tools::IsMine(unit)) {

        BWAPI::Position unit_pos = unit->getPosition();
        
        float l_min = unit_pos.getDistance(pData->ownedBases.at(0).get_pos());
        int argmin = 0;
        
        for (int i = 0; i < this->pData->ownedBases.size();i++) {
            float l = unit_pos.getDistance(this->pData->ownedBases.at(i).get_pos());
            if (l < l_min) {
                l_min = l;
                argmin = i;;
            };
        }
        this->pData->ownedBases.at(argmin).allocateWorker(unit);
    }
    
    //if unit is ressource depot : we add it to our bases list.
    else if (unit->getType() == BWAPI::Broodwar->self()->getRace().getResourceDepot()) {
        if (Tools::IsMine(unit)) {
            //we have to check if this is our starting base ! Indeed, the starting base actually
            //spawns at t=0... but it is already inside the vec ! (and it needs to be).
            if (unit->getPosition().getDistance(this->pData->basePosition) > 0) {
                this->pData->ownedBases.push_back(OwnedBase(unit->getPosition()));
                int n = this->pData->ownedBases.size();

                this->pData->ownedBases.at(n-1).dispatchWorkersToMe(&this->pData->ownedBases);
            }
        }

    }

    //if this is an extractor : add it to the the closest base.
    else if (unit->getType() == BWAPI::Broodwar->self()->getRace().getRefinery() && Tools::IsMine(unit)) {
        float l_min = unit->getPosition().getDistance(pData->ownedBases.at(0).get_pos());
        int argmin = 0;

        for (int i = 0; i < this->pData->ownedBases.size(); i++) {
            float l = unit->getPosition().getDistance(this->pData->ownedBases.at(i).get_pos());
            if (l < l_min) {
                l_min = l;
                argmin = i;;
            };
        }
        //remove the wrong worker (the one that was morphed into the extractor...
        //before : 

        this->pData->ownedBases.at(argmin).remove_imposter();
        this->pData->ownedBases.at(argmin).set_gaz(unit);
        

        for (int k = 0; k < 3; k++) {

            this->pData->ownedBases.at(argmin).allocateWorker(this->pData->ownedBases.at(argmin).worstSpot()->workers.at(0));
   
        };
    }

    

    // building debugger
    if (unit->getType().isBuilding() && Tools::IsMine(unit)) {
        BWAPI::Position pos = unit->getPosition();
        BWAPI::UnitType type = unit->getType();
        BWAPI::TilePosition tile = unit->getTilePosition();
        std::cout << "A " << type << " has been created at " << pos << "in" << tile << std::endl;
	}
}

// Called whenever a unit appears, with a pointer to the destroyed unit
// This is usually triggered when units appear from fog of war and become visible
void StarterBot::onUnitShow(BWAPI::Unit unit)
{ 
    //if unit is ressource mineral : check possibly add it to its corresponding base.
    if (unit->getType().isMineralField()) {
        for (auto& base : this->pData->ownedBases) {
            base.checkNewMineral(unit);
        }
    }

}

// Called whenever a unit gets hidden, with a pointer to the destroyed unit
// This is usually triggered when units enter the fog of war and are no longer visible
void StarterBot::onUnitHide(BWAPI::Unit unit)
{ 
	
}

// Called whenever a unit switches player control
// This usually happens when a dark archon takes control of a unit
void StarterBot::onUnitRenegade(BWAPI::Unit unit)
{ 
	
}