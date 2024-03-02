#pragma once
#include <unordered_set>
#include <queue>
#include <BWAPI.h>
#include "BuildOrder.h"
#include "OwnedBase.h"
#include <queue>
#include <Job.h>

#define THRESHOLD1_UNUSED_SUPPLY 2

#define NWANTED_WORKERS_TOTAL 20

class Blackboard {
public:
	Blackboard(): buildOrder() {}
	
	BuildOrder buildOrder;

	// purpose: if the mineral count (with self()->minerals()) update is not instant after using minerals
	// otherwise just remove this attribute
	int currMinerals; 

	int currSupply;
	int thresholdSupply = 0; // modifiable with the amount of HQ we have + unit production

	// TODO: replace with "number of workers per base" and "number of minerals per base" 
	// (not more than 2 workers / mineral, don't forget to update)
	int nWantedWorkersTotal; 

	std::unordered_set<BWAPI::Unit> unitsFarmingMinerals;

	// useful?
	int nbOverlords = 0;

	//position of OUR starting base : 
	BWAPI::Position basePosition;


	//what we need for the minerals occupency table:
	std::vector<int> minerals_indx_to_ID;
	std::map<int, int> minerals_ID_to_indx;
	std::vector<int> mineralsOccupancyTable;

	//our bases <3
	std::vector<OwnedBase> ownedBases;
	std::vector<BWAPI::Position> enemyBasesPositions{};
	BWAPI::TilePosition naturalTilePosition;
	BWAPI::TilePosition enemyNaturalTilePosition;

	// for units / techs we want right now but we don't have ressources so we don't train anything to wait for them
	std::queue<BWAPI::UnitType> unitsRequested; // for now by build order, maybe add struct for prio
	std::queue<BWAPI::TechType> techsRequested; 

	//std::unordered_set<BWAPI::Unit> unitsFarmingMinerals; //#TODO: associate them to bases (not to HQ btw)

	std::queue<Job> jobQueue;
};
