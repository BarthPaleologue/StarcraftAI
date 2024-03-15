#pragma once
#include "BT.h"
#include "Tools.h"
#include "BT_NODE.h"

class MineralSpot {
	public : 
		BWAPI::Unit mineral;
		std::vector<BWAPI::Unit> workers;

		inline MineralSpot(BWAPI::Unit min) { this->mineral = min; };
		inline void sendToMine(BWAPI::Unit worker) {
			this->workers.push_back(worker);
			worker->rightClick(mineral);
		};
};


class OwnedBase {
	private : 
		BWAPI::Position pos;
		
		std::vector<MineralSpot> minerals;
		
		int maxMineralDist = 400;
		


	public : 
		
		inline void set_pos(BWAPI::Position pos) { this->pos = pos;  create_minerals_table(); };
		inline BWAPI::Position get_pos() { return this->pos; };


		OwnedBase(BWAPI::Position pos);
		
		//initialise the minerals mining structure !
		void create_minerals_table();

		//used in the node SendIdleWorkerToMinerals. Sens the workers OF THIS BASE to work
		BT_NODE::State base_SendIdleWorkerToMinerals();
		
		MineralSpot* bestSpot();
		MineralSpot* worstSpot();

		//allocate/desallocate worker to a base : 
		void allocateWorker(BWAPI::Unit worker);
		void freeWorker(BWAPI::Unit worker);
		
		//send a precise worker from this base to destBase.
		void sendWorker(OwnedBase* destBase, BWAPI::Unit worker);
		
		//send SOME worker from "this" to dest_base;
		void sendSomeone(OwnedBase* destBase);

		//dispatch workers from other bases to my "this". 
		void dispatchWorkersToMe(std::vector<OwnedBase>* ownedBases);

		inline void print_minerals() {
			for (int i = 0; i < this->minerals.size();i++) {
				std::cout << minerals.at(i).workers.size() << " - ";
			}
			std::cout<<""<<std::endl;

		}

		//when a new mineral is discovered, we ceck if we need to add it.
		void checkNewMineral(BWAPI::Unit mineral);


};