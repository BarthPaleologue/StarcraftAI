#pragma once
#include <unordered_set>
#include <queue>
#include <BWAPI.h>
#include "buildOrder/BuildOrder.h"
#include "OwnedBase.h"
#include <queue>
#include "Job.h"
#include <map>
#include <targeting/HarassmentManager.h>
#include <set>
#include "BaseManager.h"


int const DRONE_COUNT_WHILE_MUTA_HARASS = 20;
int const ABSOLUTE_DRONE_LIMIT = 70;

const BWAPI::TilePosition NONE_POS(-1, -1);

const BWAPI::TilePosition BASE_TILE_POS[2][6] = {
	{BWAPI::TilePosition(31,7),
	BWAPI::TilePosition(63,19),
	BWAPI::TilePosition(7,28),
	BWAPI::TilePosition(7,55),
	BWAPI::TilePosition(86,38),
	BWAPI::TilePosition(86,6),},

	{BWAPI::TilePosition(64, 118),
	BWAPI::TilePosition(29, 107),
	BWAPI::TilePosition(85, 96),
	BWAPI::TilePosition(85, 70),
	BWAPI::TilePosition(6, 88),
	BWAPI::TilePosition(6, 119)}

};

const BWAPI::TilePosition START_TILE_POS[2] = {
	BWAPI::TilePosition(31,7), 
	BWAPI::TilePosition(64, 118)
};

const BWAPI::TilePosition SPAWNING_POOL_TILE_POS[2] = {
	BWAPI::TilePosition(29, 12),
	BWAPI::TilePosition(68, 114),
};

const BWAPI::TilePosition SPIRE_TILE_POS[2] = {
	BWAPI::TilePosition(63, 23),
	BWAPI::TilePosition(31, 101),
};

const BWAPI::Position DEFENCE_POS[2][7] = {
	{BWAPI::Position(1650,300),
	BWAPI::Position(2050,800),
	BWAPI::Position(480,1100),
	BWAPI::Position(553,1533),
	BWAPI::Position(2793,1311),
	BWAPI::Position(2788,322),
	BWAPI::Position(1670,275),},
	
	{BWAPI::Position(1370, 3730),
	BWAPI::Position(1050, 3250),
	BWAPI::Position(2586, 2963),
	BWAPI::Position(2550, 2501),
	BWAPI::Position(333, 2779),
	BWAPI::Position(239, 3705),
	BWAPI::Position(1386,3792),}
};

const BWAPI::Position ATTACK_POS[2][7] = {
	{BWAPI::Position(1855,488),
	BWAPI::Position(1619,1062),
	BWAPI::Position(724,1267),
	BWAPI::Position(700,1370),
	BWAPI::Position(2582,1530),
	BWAPI::Position(2976,488),
	BWAPI::Position(1852,127)},

	{BWAPI::Position(1190, 3550),
	BWAPI::Position(1468, 3026),
	BWAPI::Position(2349, 2805),
	BWAPI::Position(2351, 2651),
	BWAPI::Position(455, 2630),
	BWAPI::Position(119, 3510),
	BWAPI::Position(1214,3934),}
};

const BWAPI::Position STATION_POS[2] = {
	BWAPI::Position(1275, 1924),
	BWAPI::Position(1767, 2218)
};

enum class GameStage {
	EARLY,
	MID, //includes late for now
	LATE
};


class Blackboard {
public:
	Blackboard(BuildOrderType _boType) : buildOrder(_boType) {}

	BuildOrder buildOrder;
	
	BaseManager bases[2][6];

	GameStage gameStage = GameStage::EARLY;

	// purpose: if the mineral count (with self()->minerals()) update is not instant after using minerals
	// otherwise just remove this attribute
	int currMinerals;
	int currGas;

	BWAPI::UnitType focusedTrainingUnit = BWAPI::UnitTypes::Zerg_Zergling;

	int currSupply;
	int thresholdSupply = 0; //if it's -1 then it's calculated by overlord management 

	// TODO: replace with "number of workers per base" and "number of minerals per base" 
	// (not more than 2 workers / mineral, don't forget to update)
	int nWantedWorkersTotal;

	std::unordered_set<BWAPI::Unit> unitsFarmingMinerals;

	// useful?
	int nbOverlords = 0;

	std::map<BWAPI::UnitType, int> minRequiredUnitCount;

	//position of OUR starting base : 
	BWAPI::Position basePosition;


	//what we need for the minerals occupency table:
	std::vector<int> minerals_indx_to_ID;
	std::map<int, int> minerals_ID_to_indx;
	std::vector<int> mineralsOccupancyTable;

	//our bases <3
	std::vector<OwnedBase> ownedBases;
	std::vector<BWAPI::Position> enemyBasesPositions{};
	int myPosIdx;
	int enemyPosIdx;

	BWAPI::Race enemyRace;

	HarassmentManager harassmentManager = HarassmentManager();

	// for units / techs we want right now but we don't have ressources so we don't train anything to wait for them
	std::queue<BWAPI::UnitType> unitsRequested; // for now by build order, maybe add struct for prio
	std::queue<BWAPI::TechType> techsRequested;

	std::queue<Job> jobQueue; // priority queue?

	std::set<BWAPI::TechType> enemyTechSet;
	std::set<BWAPI::UnitType> enemyTechBuildings;

	bool EnemyHasTech(BWAPI::TechType tech) {
		return enemyTechSet.contains(tech);
	}
	bool EnemyMayHasTech(BWAPI::TechType tech) {
		return enemyTechBuildings.contains(tech.whatResearches());
	};
	bool EnemyHasBuilding(BWAPI::UnitType building) {
		return enemyTechBuildings.contains(building);
	}

	bool cantWin(){
		return !Tools::canAllIn();
	}
	bool canAllIn(){
		return Tools::canAllIn();
	}
	bool allIn = false;
};