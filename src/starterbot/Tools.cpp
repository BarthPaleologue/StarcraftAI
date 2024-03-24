#include "targeting/ForceTools.h"
#include "Tools.h"
#include "Blackboard.h"

BWAPI::Unit Tools::GetClosestUnitTo(BWAPI::Position p, const BWAPI::Unitset& units)
{
    BWAPI::Unit closestUnit = nullptr;

    for (auto& u : units)
    {
        if (!closestUnit || u->getDistance(p) < closestUnit->getDistance(p))
        {
            closestUnit = u;
        }
    }

    return closestUnit;
}

BWAPI::Unit Tools::GetClosestUnitTo(BWAPI::Unit unit, const BWAPI::Unitset& units)
{
    if (!unit) { return nullptr; }
    return GetClosestUnitTo(unit->getPosition(), units);
}

int Tools::CountUnitsOfType(BWAPI::UnitType type, const BWAPI::Unitset& units)
{
    int sum = 0;
    for (auto& unit : units)
    {
        if (unit->getType() == type || unit->getBuildType() == type)
        {
            sum++;
        }
    }

    return sum;
}
BWAPI::Unitset Tools::GetUnitsInRadius(BWAPI::Position p, float r, const BWAPI::Unitset& units) {
    BWAPI::Unitset Result;
    for (auto& u : units) {
        if (u->getPosition().getDistance(p)<r) {
            Result.insert(u);
        }
    }
    return Result;
}
BWAPI::Unit Tools::GetUnitOfType(BWAPI::UnitType type)
{
    // For each unit that we own
    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        // if the unit is of the correct type, and it actually has been constructed, return it
        if (unit->getType() == type && unit->isCompleted())
        {
            return unit;
        }
    }

    // If we didn't find a valid unit to return, make sure we return nullptr
    return nullptr;
}
void Tools::GetAllUnitsOfType(BWAPI::UnitType type, std::vector<BWAPI::Unit>& units) {
    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        // if the unit is of the correct type, and it actually has been constructed, return it
        if (unit->getType() == type && unit->isCompleted())
        {
            units.push_back(unit);
        }
    }
}
BWAPI::Unit Tools::GetUnitById(int ID,BWAPI::Unitset set) {
    //return unit which ID is corec. 
    //Carefull, we're speaking of the ID of the actual little dude, not the ID of the type.
    for (auto& unit : set)
    {
        if (unit->getID() == ID)
        {
            return unit;
        }
    }
        return nullptr;

    };

BWAPI::Unit Tools::GetDepot()
{
    const BWAPI::UnitType depot = BWAPI::Broodwar->self()->getRace().getResourceDepot();
    return GetUnitOfType(depot);
}


BWAPI::Unit Tools::GetClosestUnitOfType(BWAPI::UnitType type, BWAPI::Position position, float _distance)
{
    // For each unit that we own
    BWAPI::Unit closestUnit = nullptr;

    //BWAPI::TilePosition desiredPos = BWAPI::Broodwar->self()->getStartLocation();
    //BWAPI::Position pos(desiredPos);

    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        // if the unit is of the correct type, and it actually has been constructed, return it
        if (unit->getType() == type && unit->isCompleted())
        {
            if (unit->getDistance(position) < _distance)
            {
                _distance = unit->getDistance(position);
                closestUnit = unit;
            }
        }
    }

    // If we didn't find a valid unit to return, make sure we return nullptr
    return closestUnit;
}

BWAPI::Unit Tools::GetClosestUnitOfTypeBeingBuilt(BWAPI::UnitType type, BWAPI::Position position, float distance)
{
    // For each unit that we own
    BWAPI::Unit closestUnit = nullptr;

    //BWAPI::TilePosition desiredPos = BWAPI::Broodwar->self()->getStartLocation();
    //BWAPI::Position pos(desiredPos);

    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        // if the unit is of the correct type, and it actually has been constructed, return it
        if (unit->getType() == type)
        {
            if (unit->getDistance(position) < distance)
            {
                distance = unit->getDistance(position);
                closestUnit = unit;
            }
        }
    }

    // If we didn't find a valid unit to return, make sure we return nullptr
    return closestUnit;
}


// Attempt tp construct a building of a given type 
bool Tools::BuildBuilding(BWAPI::UnitType type)
{
    // Get the type of unit that is required to build the desired building
    BWAPI::UnitType builderType = type.whatBuilds().first;

    // Get a unit that we own that is of the given type so it can build
    // If we can't find a valid builder unit, then we have to cancel the building
    BWAPI::Unit builder = Tools::GetUnitOfType(builderType);
    if (!builder) { return false; }

    // Get a location that we want to build the building next to
    BWAPI::TilePosition desiredPos = BWAPI::Broodwar->self()->getStartLocation();

    // Ask BWAPI for a building location near the desired position for the type
    int maxBuildRange = 64;
    bool buildingOnCreep = type.requiresCreep();
    BWAPI::TilePosition buildPos = BWAPI::Broodwar->getBuildLocation(type, desiredPos, maxBuildRange, buildingOnCreep);
    return builder->build(type, buildPos);
}


bool Tools::BuildBuildingAtPosition(BWAPI::UnitType type, BWAPI::TilePosition buildPos)
{
    // Get the type of unit that is required to build the desired building
    BWAPI::UnitType builderType = type.whatBuilds().first;

    // Get a unit that we own that is of the given type so it can build
    // If we can't find a valid builder unit, then we have to cancel the building
    BWAPI::Position buildingPos(buildPos);
    BWAPI::Unit builder = Tools::GetClosestUnitOfType(builderType, buildingPos);
    //BWAPI::Unit builder = Tools::GetUnitOfType(builderType);
    if (type.mineralPrice() > BWAPI::Broodwar->self()->minerals()) {
		return false;
	}
    if (!builder) { 
        return false; }
    if (!BWAPI::Broodwar->isExplored(buildPos)) {
		builder->move(buildingPos);
        return false;
	}
    // Ask BWAPI for a building location near the desired position for the type
    int maxBuildRange = 500;
    bool buildingOnCreep = type.requiresCreep();
    BWAPI::TilePosition buildPosHere = BWAPI::Broodwar->getBuildLocation(type, buildPos, maxBuildRange, buildingOnCreep);
    return builder->build(type, buildPosHere);
}


void Tools::DrawUnitCommands()
{
    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        const BWAPI::UnitCommand & command = unit->getLastCommand();

        // If the previous command had a ground position target, draw it in red
        // Example: move to location on the map
        if (unit->isSelected())
        {
            std::string posStr = "Selected Unit Position: " + std::to_string(unit->getPosition().x) + "," + std::to_string(unit->getPosition().y);
            BWAPI::Broodwar->drawTextScreen(BWAPI::Position(20, 20), posStr.c_str() );
            std::string tileStr = "Selected Unit TilePosition: " + std::to_string(unit->getTilePosition().x) + "," + std::to_string(unit->getTilePosition().y);
            BWAPI::Broodwar->drawTextScreen(BWAPI::Position(20, 30), tileStr.c_str());
        }
        if (command.getTargetPosition() != BWAPI::Positions::None)
        {
            BWAPI::Broodwar->drawLineMap(unit->getPosition(), command.getTargetPosition(), BWAPI::Colors::Red);
        }

        // If the previous command had a tile position target, draw it in red
        // Example: build at given tile position location
        if (command.getTargetTilePosition() != BWAPI::TilePositions::None)
        {
            BWAPI::Broodwar->drawLineMap(unit->getPosition(), BWAPI::Position(command.getTargetTilePosition()), BWAPI::Colors::Green);
        }

        // If the previous command had a unit target, draw it in red
        // Example: attack unit, mine mineral, etc
        if (command.getTarget() != nullptr)
        {
            BWAPI::Broodwar->drawLineMap(unit->getPosition(), command.getTarget()->getPosition(), BWAPI::Colors::White);
        }
    }
}

void Tools::DrawUnitBoundingBoxes()
{
    for (auto& unit : BWAPI::Broodwar->getAllUnits())
    {
        BWAPI::Position topLeft(unit->getLeft(), unit->getTop());
        BWAPI::Position bottomRight(unit->getRight(), unit->getBottom());
        BWAPI::Broodwar->drawBoxMap(topLeft, bottomRight, BWAPI::Colors::White);
    }
}

void Tools::SmartRightClick(BWAPI::Unit unit, BWAPI::Unit target)
{
    // if there's no valid unit, ignore the command
    if (!unit || !target) { return; }

    // Don't issue a 2nd command to the unit on the same frame
    if (unit->getLastCommandFrame() >= BWAPI::Broodwar->getFrameCount()) { return; }

    // If we are issuing the same type of command with the same arguments, we can ignore it
    // Issuing multiple identical commands on successive frames can lead to bugs
    if (unit->getLastCommand().getTarget() == target) { return; }
    
    // If there's nothing left to stop us, right click!
    unit->rightClick(target);
}

int Tools::GetUnusedSupply(bool inProgress)
{
    int unusedSupply = Tools::GetTotalSupply(inProgress) - BWAPI::Broodwar->self()->supplyUsed();
    return unusedSupply;
}

int Tools::GetTotalSupply(bool inProgress)
{
    // start the calculation by looking at our current completed supplyt
    int totalSupply = BWAPI::Broodwar->self()->supplyTotal();

    // if we don't want to calculate the supply in progress, just return that value
    if (!inProgress) { return totalSupply; }

    // if we do care about supply in progress, check all the currently constructing units if they will add supply
    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        // ignore units that are fully completed
        if (unit->isCompleted()) { continue; }
        if (unit->getType() == BWAPI::UnitTypes::Zerg_Hatchery) continue; //negletable


        // if they are not completed, then add their supply provided to the total supply
        totalSupply += unit->getType().supplyProvided();

        //zerg specific
        if (unit->getType() == BWAPI::UnitTypes::Zerg_Egg) {
            totalSupply += unit->getBuildType().supplyProvided();
        }
    }

    // one last tricky case: if a unit is currently on its way to build a supply provider, add it
    if (BWAPI::Broodwar->self()->getRace() != BWAPI::Races::Zerg) {
        for (auto& unit : BWAPI::Broodwar->self()->getUnits())
        {
            // get the last command given to the unit
            const BWAPI::UnitCommand& command = unit->getLastCommand();

            // if it's not a build command we can ignore it
            if (command.getType() != BWAPI::UnitCommandTypes::Build) { continue; }

            // add the supply amount of the unit that it's trying to build
            totalSupply += command.getUnitType().supplyProvided();
        }
    }

    return totalSupply;
}

void Tools::DrawUnitHealthBars()
{
    // how far up from the unit to draw the health bar
    int verticalOffset = -10;

    // draw a health bar for each unit on the map
    for (auto& unit : BWAPI::Broodwar->getAllUnits())
    {
        // determine the position and dimensions of the unit
        const BWAPI::Position& pos = unit->getPosition();
        int left = pos.x - unit->getType().dimensionLeft();
        int right = pos.x + unit->getType().dimensionRight();
        int top = pos.y - unit->getType().dimensionUp();
        int bottom = pos.y + unit->getType().dimensionDown();

        // if it's a resource, draw the resources remaining
        if (unit->getType().isResourceContainer() && unit->getInitialResources() > 0)
        {
            double mineralRatio = (double)unit->getResources() / (double)unit->getInitialResources();
            DrawHealthBar(unit, mineralRatio, BWAPI::Colors::Cyan, 0);
        }
        // otherwise if it's a unit, draw the hp 
        else if (unit->getType().maxHitPoints() > 0)
        {
            double hpRatio = (double)unit->getHitPoints() / (double)unit->getType().maxHitPoints();
            BWAPI::Color hpColor = BWAPI::Colors::Green;
            if (hpRatio < 0.66) hpColor = BWAPI::Colors::Orange;
            if (hpRatio < 0.33) hpColor = BWAPI::Colors::Red;
            DrawHealthBar(unit, hpRatio, hpColor, 0);
            
            // if it has shields, draw those too
            if (unit->getType().maxShields() > 0)
            {
                double shieldRatio = (double)unit->getShields() / (double)unit->getType().maxShields();
                DrawHealthBar(unit, shieldRatio, BWAPI::Colors::Blue, -3);
            }
        }
    }
}

void Tools::DrawHealthBar(BWAPI::Unit unit, double ratio, BWAPI::Color color, int yOffset)
{
    int verticalOffset = -10;
    const BWAPI::Position& pos = unit->getPosition();

    int left = pos.x - unit->getType().dimensionLeft();
    int right = pos.x + unit->getType().dimensionRight();
    int top = pos.y - unit->getType().dimensionUp();
    int bottom = pos.y + unit->getType().dimensionDown();

    int ratioRight = left + (int)((right - left) * ratio);
    int hpTop = top + yOffset + verticalOffset;
    int hpBottom = top + 4 + yOffset + verticalOffset;

    BWAPI::Broodwar->drawBoxMap(BWAPI::Position(left, hpTop), BWAPI::Position(right, hpBottom), BWAPI::Colors::Grey, true);
    BWAPI::Broodwar->drawBoxMap(BWAPI::Position(left, hpTop), BWAPI::Position(ratioRight, hpBottom), color, true);
    BWAPI::Broodwar->drawBoxMap(BWAPI::Position(left, hpTop), BWAPI::Position(right, hpBottom), BWAPI::Colors::Black, false);

    int ticWidth = 3;

    for (int i(left); i < right - 1; i += ticWidth)
    {
        BWAPI::Broodwar->drawLineMap(BWAPI::Position(i, hpTop), BWAPI::Position(i, hpBottom), BWAPI::Colors::Black);
    }

 
}

bool Tools::IsMine(BWAPI::Unit unit) {
    return unit->getPlayer() == BWAPI::Broodwar->self();
}


bool Tools::TrainBuilderAtBase(BWAPI::Unit base, int num) {	
    std::vector<BWAPI::Unit> larvas;
    Tools::GetAllUnitsOfType(BWAPI::UnitTypes::Zerg_Larva, larvas);

    // filtering to only get larvas that are not morphing
    std::vector<BWAPI::Unit> lavasNearby;
    for (auto larva : larvas) {
        if (larva->isMorphing()) continue;
        if (larva->getPosition().getDistance(base->getPosition()) < 200) {
			lavasNearby.push_back(larva);
		}
    }
    for (int i = 0; i < num; i++) {
		if (lavasNearby.size() == 0) {
			return false;
		}
		BWAPI::Unit larva = lavasNearby.back();
		lavasNearby.pop_back();
		larva->train(BWAPI::UnitTypes::Zerg_Drone);
	}
}


bool Tools::cantWin(){
    BWAPI::Player enemy = BWAPI::Broodwar->enemy();
	BWAPI::Player me = BWAPI::Broodwar->self();

	BWAPI::UnitType myWorker =me->getRace().getWorker();
	BWAPI::UnitType enemyWorker =enemy->getRace().getWorker();


	//compute my score : 
	float myDPS=0;
	float enemyDPS=0;
    float myHp=0;
	float enemyHp=0;
    float myCount=0;
    float enemyCount=0;

    myDPS=12*ForceTools::unitDPS(BWAPI::UnitTypes::Zerg_Zergling,me, enemyWorker,enemy);
    myHp=12*BWAPI::UnitTypes::Zerg_Zergling.maxHitPoints();

	myDPS=myDPS/enemyWorker.maxHitPoints();
	float myScore = myDPS * pow(myHp, 1.5);



	//compute enemy score : 
	for (auto& unit : enemy->getUnits()){
		float dps = ForceTools::unitDPS(unit->getType(),enemy,myWorker,me);
		if(dps>0){
			enemyDPS+=dps;
			enemyHp+=unit->getType().maxHitPoints();
            enemyCount++;
		}
	}


    enemyDPS =enemyDPS/myWorker.maxHitPoints();
	float enemyScore = enemyDPS * pow(enemyHp, 1.5);
	

	return (enemyScore>myScore);

}

bool Tools::canAllIn(){
    BWAPI::Player enemy = BWAPI::Broodwar->enemy();
	BWAPI::Player me = BWAPI::Broodwar->self();

	BWAPI::UnitType myWorker =me->getRace().getWorker();
	BWAPI::UnitType enemyWorker =enemy->getRace().getWorker();


	//compute my score : 
	float myDPS=0;
	float enemyDPS=0;
    float myHp=0;
	float enemyHp=0;
    float myCount=0;
    float enemyCount=0;

	for (auto& unit : me->getUnits()){
		float dps = ForceTools::unitDPS(unit->getType(),me,enemyWorker,enemy);;
		if(dps>0 && myWorker !=unit->getType()){
			myDPS+=dps;
			myHp+=unit->getType().maxHitPoints();
            myCount++;
		}
	}
	myDPS=myDPS/enemyWorker.maxHitPoints();
	float myScore = myDPS * pow(myHp, 1.5);



	//compute enemy score : 
	for (auto& unit : enemy->getUnits()){
		float dps = ForceTools::unitDPS(unit->getType(),enemy,myWorker,me);
		if(dps>0){
			enemyDPS+=dps;
			enemyHp+=unit->getType().maxHitPoints();
            enemyCount++;
		}
	}


    enemyDPS =enemyDPS/myWorker.maxHitPoints();
	float enemyScore = enemyDPS * pow(enemyHp, 1.5);
	

	if(enemyScore>myScore) return false;
    float remainingPercent = pow(1 - (enemyScore / myScore), (1 / (1.5)));

    //check early game : 
    if(enemyCount<20 && myCount<20){
        if(remainingPercent>0.1) return true;
        return false;
    }

    //else :
	if(remainingPercent>0.25) return true;

	return false;
}