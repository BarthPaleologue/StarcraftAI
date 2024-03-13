#include "OwnedBase.h"

OwnedBase::OwnedBase(BWAPI::Position pos) {
	this->pos = pos;
	this->create_minerals_table();
}

void OwnedBase::create_minerals_table() {
    BWAPI::Unitset myMinerals = BWAPI::Broodwar->getMinerals();

    float r = 400;
    BWAPI::Unitset CANDIDATES;
    CANDIDATES = Tools::GetUnitsInRadius(pos, r, myMinerals);
    for (auto& u : CANDIDATES) {

        this->minerals.push_back(MineralSpot(u));
    }

}

MineralSpot* OwnedBase::bestSpot() {
    int argmin = 0;
    int my_min = this->minerals.at(0).workers.size();
    for (int i = 0; i < this->minerals.size(); i++) {
        MineralSpot mineral = minerals.at(i);
        if (mineral.workers.size() < my_min) {
            argmin = i;
            my_min = mineral.workers.size();
        }
    }
    return &minerals.at(argmin);
}

MineralSpot* OwnedBase::worstSpot() {
    int argmax = 0;
    int my_max = this->minerals.at(0).workers.size();
    for (int i = 0; i < this->minerals.size(); i++) {
        MineralSpot mineral = minerals.at(i);
        if (mineral.workers.size() > my_max) {
            argmax = i;
            my_max= mineral.workers.size();
        }
    }
    return &minerals.at(argmax);
}

BT_NODE::State OwnedBase::base_SendIdleWorkerToMinerals() {
       
    MineralSpot* BestSpot = this->bestSpot();
    for (MineralSpot min : this->minerals) {
        for (BWAPI::Unit worker : min.workers) {
            if (worker->isIdle()) {
                BestSpot->sendToMine(worker);
                this->base_SendIdleWorkerToMinerals();
                return BT_NODE::SUCCESS;
            }
        }
    }
    return BT_NODE::FAILURE;
}

void OwnedBase::allocateWorker(BWAPI::Unit worker) {
    if (worker->getType() != BWAPI::Broodwar->self()->getRace().getWorker()) {
        return;
    }
    this->freeWorker(worker);
    this->bestSpot()->sendToMine(worker);
}

void OwnedBase::freeWorker(BWAPI::Unit worker) {
    if (worker->getType() != BWAPI::Broodwar->self()->getRace().getWorker()) {
            return;
    }
    std::cout << " - trying to free - " << std::endl;
    for (MineralSpot m : this->minerals) {
        for (int i = 0; i < (& (& m)->workers)->size(); i++) {
            if ((&(&m)->workers)->at(i) == worker) {
                (&(&m)->workers)->erase((&(&m)->workers)->begin()+i);
            }
        }
    }


}

void OwnedBase::sendWorker(OwnedBase* baseDest, BWAPI::Unit worker) {
    if (worker->getType() != BWAPI::Broodwar->self()->getRace().getWorker()) {
        return;
    }
    baseDest->allocateWorker(worker);
}
;

void OwnedBase::sendSomeone(OwnedBase* destBase) {
    //send a worker that is mining : we choose one that is mining the most saturated spot.

    MineralSpot* worst = this->worstSpot();
    this->sendWorker(destBase, worst->workers.at(0));
};



void OwnedBase::dispatchWorkersToMe(std::vector<OwnedBase>* ownedBases) {

    float maxDist = 2000;
    int max_workers_to_move=6;
    //first : select all the bases that are close.
    //then : 
    
    for (int k = 0; k < max_workers_to_move; k++) {
        for (int i = 0; i < ownedBases->size();i++) {
            OwnedBase base = ownedBases->at(i);
            float dist = base.pos.getDistance(this->pos);
            if (dist > 0 && dist < maxDist) {
                if (base.worstSpot()->workers.size() > this->bestSpot()->workers.size()
                    && base.worstSpot()->workers.size() > 2) {
                    base.sendSomeone(this);
                    break;
                }
            }
        }

    }
    
};
