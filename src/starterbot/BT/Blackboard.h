#pragma once
#include <unordered_set>
#include <queue>
#include <BWAPI.h>
#include "buildOrder/BuildOrder.h"
#include "OwnedBase.h"
#include <queue>
#include "Job.h"
#include <map>

#define THRESHOLD1_UNUSED_SUPPLY 2
#define NWANTED_WORKERS_TOTAL 20

const BWAPI::TilePosition NONE_POS(-1, -1);

const BWAPI::TilePosition BASE_TILE_POS[2][6] = {
	{BWAPI::TilePosition(31,7),
	BWAPI::TilePosition(63,19),
	BWAPI::TilePosition(86,38),
	BWAPI::TilePosition(7,28),
	BWAPI::TilePosition(7,55),
	BWAPI::TilePosition(86,6),},

	{BWAPI::TilePosition(64, 118),
	BWAPI::TilePosition(29, 107),
	BWAPI::TilePosition(6, 88),
	BWAPI::TilePosition(85, 96),
	BWAPI::TilePosition(85, 70),
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

class Blackboard {
public:
	Blackboard(e_buildOrderType _boType): buildOrder(_boType) {}
	
	BuildOrder buildOrder;

	// purpose: if the mineral count (with self()->minerals()) update is not instant after using minerals
	// otherwise just remove this attribute
	int currMinerals; 

	BWAPI::UnitType focusedTrainingUnit = BWAPI::UnitTypes::Zerg_Drone;

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

	// for units / techs we want right now but we don't have ressources so we don't train anything to wait for them
	std::queue<BWAPI::UnitType> unitsRequested; // for now by build order, maybe add struct for prio
	std::queue<BWAPI::TechType> techsRequested; 

	std::queue<Job> jobQueue; // priority queue?
};
