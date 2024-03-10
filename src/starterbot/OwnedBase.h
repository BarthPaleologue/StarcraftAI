#pragma once
#include "BT.h"
#include "Tools.h"
#include "BT_NODE.h"

class OwnedBase {
	private : 
		BWAPI::Position pos;
		
		//Minerals : 
		std::vector<int> minerals_indx_to_ID;
		std::map<int, int> minerals_ID_to_indx;
		std::vector<int> mineralsOccupancyTable;
		//key : worker ID, value : associated Mineral Id;
		
		std::vector<BWAPI::Unit> baseWorkers;
		std::map<int, int> workerMineralTable;
		


	public : 
		
		inline void set_pos(BWAPI::Position pos) { this->pos = pos;  create_minerals_table(); };
		inline BWAPI::Position get_pos() { return this->pos; };


		OwnedBase(BWAPI::Position pos);
		
		//initialise the minerals mining structure !
		void create_minerals_table();

		//used in the node SendIdleWorkerToMinerals. Sens the workers OF THIS BASE to work
		BT_NODE::State base_SendIdleWorkerToMinerals();
		
		//allocate/desallocate worker to a base : 
		void allocateWorker(BWAPI::Unit worker);
		void desallocateWorker(BWAPI::Unit worker);
		
		//send a precise worker from this base to destBase.
		void sendWorker(OwnedBase* destBase, BWAPI::Unit worker);
		
		//send SOME worker from "this" to dest_base;
		void sendSomeone(OwnedBase* destBase);

		//dispatch workers from other bases to my "this". 
		void dispatchWorkersToMe(std::vector<OwnedBase> ownedBases);

};