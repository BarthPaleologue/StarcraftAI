#include "StarterBot.h"
#include "Tools.h"
#include "MapTools.h"
#include <Blackboard.h>
#include <format>

#include "BT.h"
#include <OverlordUtils.h>
#include <ZerglingUtils.h>

StarterBot::StarterBot()
{
    pData = new Blackboard();
    pData->currMinerals = 0;
    pData->currSupply = 0;
    pData->thresholdSupply = 0;

    pData->nWantedWorkersTotal = NWANTED_WORKERS_TOTAL;

    //pBtTest = nullptr;
    /*
    //Test BT nodes: BT_DECO_COND_GREATER_THAN, BT_DECO_COND_LESSER_THAN, BT_ACTION_LOG
    pBtTest = new BT_DECORATOR("EntryPoint", nullptr);
    BT_DECO_REPEATER* pForeverRepeater = new BT_DECO_REPEATER("RepeatForever", pBtTest, 0, true, false, false);
    //BT_DECO_COND_GREATER_THAN<int>* pGreaterThan = new BT_DECO_COND_GREATER_THAN<int>("MineralsGreaterThanThreshold1", pForeverRepeater, THRESHOLD1_MINERALS, pData->currMinerals, false);
    //BT_ACTION_LOG* pLog = new BT_ACTION_LOG("LogMSG", pGreaterThan, std::format("current minerals greater than {}", THRESHOLD1_MINERALS));
    BT_DECO_COND_LESSER_THAN<int>* pLesserThan = new BT_DECO_COND_LESSER_THAN<int>("MineralsLesserThanThreshold1", pForeverRepeater, THRESHOLD1_MINERALS, pData->currMinerals, false);
    BT_ACTION_LOG* pLog = new BT_ACTION_LOG("LogMSG", pLesserThan, std::format("current minerals lesser than {}", THRESHOLD1_MINERALS));
    */

    //Test BT nodes: BT_DECO_REPEATER (resetOnRepeat = true), BT_COND_GREATER_THAN, BT_COND_LESSER_THAN, BT_ACTION_LOG
    //pBtTest = new BT_DECORATOR("EntryPoint", nullptr);
    //BT_DECO_REPEATER* pForeverRepeater = new BT_DECO_REPEATER("RepeatForever", pBtTest, 0, true, false, true);
    //BT_SEQUENCER* pSequencer = new BT_SEQUENCER("sequencer",pForeverRepeater, 2);
    //BT_COND_GREATER_THAN<int> *pGreaterThan = new BT_COND_GREATER_THAN<int>("MineralsGreaterThanThreshold1",pSequencer,100, pData->currMinerals, false);
    //BT_ACTION_LOG* pLog = new BT_ACTION_LOG("LogMSG", pSequencer, std::format("current minerals greater than {}", 100));
    //BT_COND_LESSER_THAN<int>* pLesserThan = new BT_COND_LESSER_THAN<int>("MineralsLesserThanThreshold1", pSequencer, 100, pData->currMinerals, false);
    //BT_ACTION_LOG* pLog = new BT_ACTION_LOG("LogMSG", pSequencer, std::format("current minerals lesser than {}", 100));



    // Starcraft AI BT
    pBT = new BT_DECORATOR("EntryPoint", nullptr);
    
    BT_PARALLEL_SEQUENCER* pMainParallelSeq = new BT_PARALLEL_SEQUENCER("MainParallelSequence", pBT, 10);

    //Farming Minerals forever
    BT_DECO_REPEATER* pFarmingMineralsForeverRepeater = new BT_DECO_REPEATER("RepeatForeverFarmingMinerals", pMainParallelSeq, 0, true, false, true);
    BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS* pSendWorkerToMinerals = new BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS("SendWorkerToMinerals", pFarmingMineralsForeverRepeater);

    // ---- testing "BT_DECO_COND_NOT_ENOUGH_UNIT" -----
    //BT_DECO_REPEATER* pTestingDecoCondNotEnoughUnit = new BT_DECO_REPEATER("TestingDecoCondNotEnoughUnit", pMainParallelSeq, 0, true, false, true);
    //BT_DECO_CONDITION_NOT_ENOUGH_UNIT* pTest = new BT_DECO_CONDITION_NOT_ENOUGH_UNIT("test", pTestingDecoCondNotEnoughUnit, BWAPI::UnitTypes::Zerg_Evolution_Chamber, 2);
    //BWAPI::TilePosition NONE_POS(-1, -1);
    //BT_ACTION_BUILD* pBuildEvolutionChambers = new BT_ACTION_BUILD("buildEvoChambers", BWAPI::UnitTypes::Zerg_Evolution_Chamber, NONE_POS, pTest);

    // ---------------------- HQ (Hatchery, Lair, Hive) management ---------------------

    // actually modifiable into a larva management
    BT_DECO_REPEATER* pHQActionRepeater = new BT_DECO_REPEATER("RepeatForeverHQAction", pMainParallelSeq, 0, true, false, true);
    BT_SELECTOR* selectHQAction = new BT_SELECTOR("SelectHQAction", pHQActionRepeater, 10);

    // check if not sparing minerals for tasks already required from elsewhere
    BT_DECO_INVERTER* pDecoMineralsRequiredElsewhere = new BT_DECO_INVERTER("DecoMineralsRequiredElsewhere", selectHQAction);
    BT_COND_NOTHING_REQUESTED* pNothingElseRequested = new BT_COND_NOTHING_REQUESTED("CondNothingElseRequested", pDecoMineralsRequiredElsewhere);

    // Build Natural Base
    // make sure scout before that
    //BT_ACTION_BUILD* pBuildNaturalBase = new BT_ACTION_BUILD("BuildNaturalBase", BWAPI::UnitTypes::Zerg_Hatchery, pData->naturalTilePosition,selectHQAction);

    //Build Additional overlords
    //BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY* pNotEnoughSupply = new BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY("NotEnoughSupply", selectHQAction);
    //BT_ACTION_TRAIN_UNIT* pBuildSupplyProvider = new BT_ACTION_TRAIN_UNIT("BuildSupplyProvider", BWAPI::UnitTypes::Zerg_Overlord, false, pNotEnoughSupply);
    OverlordUtils::CreateTrainingTree(selectHQAction);

    //Training Workers
    BT_DECO_CONDITION_NOT_ENOUGH_WORKERS* pNotEnoughWorkers = new BT_DECO_CONDITION_NOT_ENOUGH_WORKERS("NotEnoughWorkers", selectHQAction);
    BT_ACTION_TRAIN_UNIT* pTrainWorker = new BT_ACTION_TRAIN_UNIT("TrainWorker", BWAPI::UnitTypes::Zerg_Drone, false, pNotEnoughWorkers);

    // Handling build order finished
    BT_DECO_CONDITION_BUILD_ORDER_FINISHED* buildOrderFinished = new BT_DECO_CONDITION_BUILD_ORDER_FINISHED("BuildOrderFinished", selectHQAction);
    BT_PARALLEL_SEQUENCER* buildOrderFinishedSequencer = new BT_PARALLEL_SEQUENCER("BuildOrderFinishedSequencer", buildOrderFinished, 10);

    BT_DECO_RETURN_SUCCESS* sucessTrainingZergling = new BT_DECO_RETURN_SUCCESS("SucessTrainingZergling", buildOrderFinishedSequencer);
    BT_ACTION_TRAIN_UNIT* trainZergling = new BT_ACTION_TRAIN_UNIT("TrainZergling", BWAPI::UnitTypes::Zerg_Zergling, true, sucessTrainingZergling);

    // ---------------------- End of HQ management ---------------------
}

//functions needed for initialisating : 
void StarterBot::save_base_position() {
    //We look for a hatchery, and save its position. 
    BWAPI::Unit base = Tools::GetUnitOfType(BWAPI::UnitType(131));

    BWAPI::Position base_pos = base->getPosition();
    BWAPI::TilePosition base_tile_pos = base->getTilePosition();
    this->pData->basePosition = base_pos;
    // TODO: check consistency, as position is supposed to be TilePosition * 32
    //       which doesn't seem to be the case here!
    if (base_tile_pos == BWAPI::TilePosition(31, 7)) {
		this->pData->enemyBasesPositions.push_back(BWAPI::Position(2112, 3824));
        //this->pData->naturalPosition = BWAPI::Position(992, 3472);
        //this->pData->enemyNaturalPosition = BWAPI::Position(2080, 656);
        this->pData->naturalTilePosition = BWAPI::TilePosition(63, 19);
        this->pData->enemyNaturalTilePosition = BWAPI::TilePosition(29, 107);
	}
	else { // base_tile_pos == BWAPI::TilePosition(64, 118)
		this->pData->enemyBasesPositions.push_back(BWAPI::Position(1056, 272));
        this->pData->naturalTilePosition = BWAPI::TilePosition(29, 107);
        this->pData->enemyNaturalTilePosition = BWAPI::TilePosition(63, 19);
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
    float n;




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
    
    // AI BT
    if (pBT != nullptr && pBT->Evaluate(pData) != BT_NODE::RUNNING)
    {
        std::cout << "end of BT execution" << std::endl;
        delete (BT_DECORATOR*)pBT;
        pBT = nullptr;
    }

    // iterate over all units, those who don't yet have a BT will be assigned one
    BWAPI::Unitset allUnits = BWAPI::Broodwar->self()->getUnits();
    for (auto it = allUnits.begin(); it != allUnits.end(); ++it) {
        BWAPI::Unit unit = *it;
		if (unit == nullptr) continue; // the unit is null (should not happen)
		if (!unit->exists()) continue; // the unit does not exist (dead)
        if (m_unitBT.count(unit)) continue; // the unit already has a BT
        if (!unit->isCompleted()) continue; // the unit is not completed
        if (unit->getType() == BWAPI::UnitTypes::Zerg_Egg) continue; // the unit is an egg, we will assign a BT once it is a true unit
		if (unit->getType() == BWAPI::UnitTypes::Zerg_Larva) continue; // the unit is a larva, we will assign a BT once it is a true unit

		switch (unit->getType()) {
		case BWAPI::UnitTypes::Zerg_Overlord:
			m_unitBT.insert(std::make_pair(unit, OverlordUtils::CreateIndividualTree(unit)));
			break;
            
		case BWAPI::UnitTypes::Zerg_Zergling: {
			m_unitBT.insert(std::make_pair(unit, ZerglingUtils::CreateTree(unit)));
			break;
		}
		default:
			m_unitBT.insert(std::make_pair(unit, new BT_ACTION_LOG("DoNothing", nullptr, "Do nothing")));
		}
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
    }

    //Test BT
    /*if (pBtTest != nullptr && pBtTest->Evaluate(pData) != BT_NODE::RUNNING)
    {
        delete (BT_DECORATOR*)pBtTest;
        pBtTest = nullptr;
    }*/

    /*
    // Send our idle workers to mine minerals so they don't just stand there
    sendIdleWorkersToMinerals();

    // Train more workers so we can gather more income
    trainAdditionalWorkers();

    // Build more supply if we are going to run out soon
    buildAdditionalSupply();
    */

    // Draw unit health bars, which brood war unfortunately does not do
    Tools::DrawUnitHealthBars();

    // Draw some relevent information to the screen to help us debug the bot
    drawDebugInformation();
}

// Send our idle workers to mine minerals so they don't just stand there
void StarterBot::sendIdleWorkersToMinerals()
{
    // Let's send all of our starting workers to the closest mineral to them
    // First we need to loop over all of the units that we (BWAPI::Broodwar->self()) own
    const BWAPI::Unitset& myUnits = BWAPI::Broodwar->self()->getUnits();
    for (auto& unit : myUnits)
    {
        // Check the unit type, if it is an idle worker, then we want to send it somewhere
        if (unit->getType().isWorker() && unit->isIdle())
        {
            // Get the closest mineral to this worker unit
            BWAPI::Unit closestMineral = Tools::GetClosestUnitTo(unit, BWAPI::Broodwar->getMinerals());

            // If a valid mineral was found, right click it with the unit in order to start harvesting
            if (closestMineral) { unit->rightClick(closestMineral); }
        }
    }
}

// Train more workers so we can gather more income
void StarterBot::trainAdditionalWorkers()
{
    const BWAPI::UnitType workerType = BWAPI::Broodwar->self()->getRace().getWorker();
    const int workersWanted = 20;
    const int workersOwned = Tools::CountUnitsOfType(workerType, BWAPI::Broodwar->self()->getUnits());

    if (workersOwned < workersWanted)
    {
        // get the unit pointer to my depot
        const BWAPI::Unit myDepot = Tools::GetDepot();

        // if we have a valid depot unit and it's currently not training something, train a worker
        // there is no reason for a bot to ever use the unit queueing system, it just wastes resources
        if (myDepot && !myDepot->isTraining()) { myDepot->train(workerType); }
    }
}

// Build more supply if we are going to run out soon
void StarterBot::buildAdditionalSupply()
{
    // Get the amount of supply supply we currently have unused
    const int unusedSupply = Tools::GetTotalSupply(true) - BWAPI::Broodwar->self()->supplyUsed();

    // If we have a sufficient amount of supply, we don't need to do anything
    if (unusedSupply >= 2) { return; }

    // Otherwise, we are going to build a supply provider
    const BWAPI::UnitType supplyProviderType = BWAPI::Broodwar->self()->getRace().getSupplyProvider();

    const bool startedBuilding = Tools::BuildBuilding(supplyProviderType);
    if (startedBuilding)
    {
        BWAPI::Broodwar->printf("Started Building %s", supplyProviderType.getName().c_str());
    }
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
	//if the unit is farming then remove it from data structure
    if (pData->unitsFarmingMinerals.contains(unit)) pData->unitsFarmingMinerals.erase(unit);
}

// Called whenever a unit is morphed, with a pointer to the unit
// Zerg units morph when they turn into other units
void StarterBot::onUnitMorph(BWAPI::Unit unit)
{
	
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
    // debug message when a unit is created
    if (unit->getType() == BWAPI::UnitTypes::Zerg_Hatchery) {
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