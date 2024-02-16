#pragma once
#include <unordered_set>
#include <queue>
#include <BWAPI.h>
#include "BuildOrder.h"
#include <queue>
#include <Job.h>

#define THRESHOLD1_MINERALS 200
#define THRESHOLD1_UNUSED_SUPPLY 2

#define NWANTED_WORKERS_TOTAL 20

class Blackboard {
public:
	Blackboard(): buildOrder() {}
	
	BuildOrder buildOrder;

	int currMinerals;
	int thresholdMinerals;
	int currSupply;
	int thresholdSupply = 0; // modifiable with the amount of HQ we have
	
	// TODO: replace these with something depending on the mineral count of bases
	int nWantedWorkersTotal;
	//int nWantedWorkersFarmingMinerals;

	int nbOverlords = 0;

	std::unordered_set<BWAPI::Unit> unitsFarmingMinerals;

	//position of OUR starting base : 
	BWAPI::Position basePosition;

	//what we need for the minerals occupency table:
	std::vector<int> minerals_indx_to_ID;
	std::map<int, int> minerals_ID_to_indx;
	std::vector<int> mineralsOccupancyTable;

	std::vector<BWAPI::Position> ennemyBasesPositions{};

	// for units / techs we want right now but we don't have ressources so we don't train anything to wait for them
	std::queue<BWAPI::UnitType> unitsRequested; // for now by build order, maybe add struct for prio
	std::queue<BWAPI::TechType> techsRequested; 

	//std::unordered_set<BWAPI::Unit> unitsFarmingMinerals; //#TODO: associate them to bases (not to HQ btw)

	std::queue<Job> jobQueue;
};
