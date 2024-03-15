#include "OwnedBase.h"

OwnedBase::OwnedBase(BWAPI::Position pos) {
	this->pos = pos;
	this->create_minerals_table();
}

void OwnedBase::create_minerals_table() {

    //you have to wait a little bit for the minerals to be seen !!
    _sleep(100);
    BWAPI::Unitset myMinerals = BWAPI::Broodwar->getMinerals();

    float r = 600;
    BWAPI::Unitset CANDIDATES;
    CANDIDATES = Tools::GetUnitsInRadius(pos, r, myMinerals);
    for (auto& u : CANDIDATES) {
        
        this->minerals.push_back(ResourceSpot(u));
    }
}

ResourceSpot* OwnedBase::bestSpot() {

    int argmin = 0;
    int my_min = this->minerals.at(0).workers.size();
    for (int i = 0; i < this->minerals.size(); i++) {
        ResourceSpot mineral = minerals.at(i);
        if (mineral.workers.size() < my_min) {
            argmin = i;
            my_min = mineral.workers.size();
        }
    }
    return &minerals.at(argmin);
}

ResourceSpot* OwnedBase::worstSpot() {

    int argmax = 0;
    int my_max = this->minerals.at(0).workers.size();
    for (int i = 0; i < this->minerals.size(); i++) {
        ResourceSpot mineral = minerals.at(i);
        if (mineral.workers.size() > my_max) {
            argmax = i;
            my_max= mineral.workers.size();
        }
    }
    return &minerals.at(argmax);
}

BT_NODE::State OwnedBase::base_SendIdleWorkerToMinerals() {

    for (ResourceSpot min : this->minerals) {
        ResourceSpot* BestSpot = this->bestSpot();

        for (BWAPI::Unit worker : min.workers) {
            if (worker->isIdle()&&worker->getType()==BWAPI::Broodwar->self()->getRace().getWorker()) {
                this->allocateWorker(worker);
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
    //get the number fo people mining minerals.
    int sum = 0;
    for (auto m : this->minerals) {
        sum += m.workers.size();
    }

    if (this->has_gaz()&&this->gaz.workers.size()<3 && sum>0) {
        this->get_gaz()->sendToMine(worker);
        return;
    }
    else {
        this->bestSpot()->sendToMine(worker);
    }
}

void OwnedBase::freeWorker(BWAPI::Unit worker) {
    for (int i = 0; i < this->minerals.size(); i++) {
        this->minerals.at(i).freeFromMine(worker);
    }
    if (has_gaz()) {
        this->gaz.freeFromMine(worker);
    }


}

void OwnedBase::sendWorker(OwnedBase* baseDest, BWAPI::Unit worker) {

    if (worker->getType() != BWAPI::Broodwar->self()->getRace().getWorker()) {
        return;
    }
    this->freeWorker(worker);
    baseDest->allocateWorker(worker);
}
;

void OwnedBase::sendSomeone(OwnedBase* destBase) {

    //send a worker that is mining : we choose one that is mining the most saturated spot.

    ResourceSpot* worst = this->worstSpot();
    if (worst->workers.size() > 0) {
        this->sendWorker(destBase, worst->workers.at(0));
    }
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
            if (dist > 0 && dist < maxDist && base.get_pos().getDistance(this->get_pos())>1) {
                if (base.worstSpot()->workers.size() > this->bestSpot()->workers.size()
                    && base.worstSpot()->workers.size() > 2) {
                    base.sendSomeone(this);
                    break;
                }
            }
        }

    }
    
};

void OwnedBase::checkNewMineral(BWAPI::Unit mineral) {
    if (this->pos.getDistance(mineral->getPosition()) < this->maxMineralDist) {
        //check if not already there : 
        for (ResourceSpot my_min : this->minerals) {
            if (my_min.field == mineral) {
                return;
            }
        }
        this->minerals.push_back(ResourceSpot(mineral));

    }

}

void OwnedBase::remove_imposter() {
    std::vector<BWAPI::Unit> actual_workers;
    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        // if the unit is of the correct type, and it actually has been constructed, return it
        if (unit->getType() == BWAPI::Broodwar->self()->getRace().getWorker() && unit->isCompleted())
        {
            actual_workers.push_back(unit);
        }
    }

    for (int i = 0; i < this->minerals.size(); i++) {
        for (int j = 0; j < this->minerals.at(i).workers.size(); j++) {
            BWAPI::Unit tested_worker = this->minerals.at(i).workers.at(j);
            bool found = false;
            for(auto& actual_worker : actual_workers){
                if (actual_worker == tested_worker) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                this->minerals.at(i).workers.erase(this->minerals.at(i).workers.begin() + j);
            }
        }
    }
};
