#pragma once
#include "BT.h"
#include "Tools.h"
#include "BT_NODE.h"

class ResourceSpot {
	public : 
		BWAPI::Unit field;
		std::vector<BWAPI::Unit> workers;

		inline ResourceSpot(BWAPI::Unit min) { this->field = min; };
		
		inline void sendToMine(BWAPI::Unit worker) {
			this->workers.push_back(worker);
			worker->rightClick(field);
		};

		inline void freeFromMine(BWAPI::Unit worker) {
			for (int i = 0; i < workers.size(); i++) {
				if (worker == workers.at(i)) {
					workers.erase(workers.begin() + i);
					return;
				}
			}
		}
};



class OwnedBase {
	private : 
		BWAPI::Position pos;
		
		std::vector<ResourceSpot> minerals;
		
		bool has_ext=false;
		ResourceSpot gaz = nullptr;

		int maxMineralDist = 400;
		


	public : 
		
		inline void set_pos(BWAPI::Position pos) { this->pos = pos;  create_minerals_table(); };
		inline BWAPI::Position get_pos() { return this->pos; };

		inline void set_gaz(BWAPI::Unit extractor) {
			if (extractor->getType() == BWAPI::Broodwar->self()->getRace().getRefinery() && Tools::IsMine(extractor)) {
				this->gaz = ResourceSpot(extractor);
				this->has_ext = true;
			}

		};
		inline ResourceSpot* get_gaz() { return &this->gaz; };
		inline bool has_gaz() { return this->has_ext; };
		OwnedBase(BWAPI::Position pos);
		
		//initialise the minerals mining structure !
		void create_minerals_table();

		//used in the node SendIdleWorkerToMinerals. Sens the workers OF THIS BASE to work
		BT_NODE::State base_SendIdleWorkerToMinerals();
		
		ResourceSpot* bestSpot();
		ResourceSpot* worstSpot();

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
		inline void print_gaz() {
			std::cout << "gaz : ";
			if (!has_gaz()) {
				std::cout << " 0 " << std::endl;
			}
			else{
				std::cout << this->gaz.workers.size() << std::endl;
			}


		}

		//when a new mineral is discovered, we ceck if we need to add it.
		void checkNewMineral(BWAPI::Unit mineral);

		//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
		void remove_imposter();
};