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

    int count = 0;
    for (auto& u : CANDIDATES) {

        this->minerals_indx_to_ID.push_back(u->getID());
        this->minerals_ID_to_indx[count] = u->getID();
        mineralsOccupancyTable.push_back(0);
        count++;

    }
}

BT_NODE::State OwnedBase::base_SendIdleWorkerToMinerals() {

    BT_NODE::State result = BT_NODE::FAILURE;
    for (auto& unit : this->baseWorkers)
    {

        if (unit->isIdle())
        {
            std::vector<int> table = mineralsOccupancyTable;
            //find min:
            int min = table.at(0);
            int min_id = 0;
            for (int i = 0; i < table.size(); i++) {
                if (table.at(i) < min) {
                    min = table.at(i);
                    min_id = i;
                }
            }
            int mineralID = minerals_indx_to_ID.at(min_id);
            BWAPI::Unit mineralTarget = Tools::GetUnitById(mineralID, BWAPI::Broodwar->getMinerals());

            unit->rightClick(mineralTarget);

            mineralsOccupancyTable.at(min_id)++;
            this->workerMineralTable.insert(std::pair<int,int>(unit->getID(), mineralID));
            result = BT_NODE::SUCCESS;
        }

    }
    return result;

}

void OwnedBase::allocateWorker(BWAPI::Unit worker) {
    if (worker->getType() !=  BWAPI::Broodwar->self()->getRace().getWorker()) {
        return;
    }
    std::vector<BWAPI::Unit> a;
    for (int i = 0; i < this->baseWorkers.size(); i++) {
        a.push_back(this->baseWorkers.at(i));
    }
    a.push_back(worker);
    this->baseWorkers=a;

}

void OwnedBase::desallocateWorker(BWAPI::Unit worker) {
    if (worker->getType() != BWAPI::Broodwar->self()->getRace().getWorker()) {
            return;
    }
    
    int workerID = worker->getID();
    int to_kill = 0;

    //try to desallocate worker, if it was allocated.
    for (auto& worker : this->baseWorkers) {
        if (worker->getID() == workerID) {
            int mineralId = workerMineralTable.at(to_kill);
            workerMineralTable.erase(to_kill);
            
            int mineralIndx = minerals_ID_to_indx.at(mineralId);
            mineralsOccupancyTable.at(mineralIndx)--;
            return;
        }
        to_kill++;
    }
}

void OwnedBase::sendWorker(OwnedBase* baseDest, BWAPI::Unit worker) {
    if (worker->getType() != BWAPI::Broodwar->self()->getRace().getWorker()) {
        return;
    }

    this->desallocateWorker(worker);
    baseDest->allocateWorker(worker);
    worker->rightClick(baseDest->pos);
}
;

void OwnedBase::sendSomeone(OwnedBase* destBase) {
    //send a worker that is mining : we choose one that is mining the most saturated spot.

    int argmax = 0;
    int max = mineralsOccupancyTable.at(0);
    for (int i = 0; i < mineralsOccupancyTable.size(); i++) {
        int o = mineralsOccupancyTable.at(i);
        if (o > max) {
            argmax = i;
            max = 0;
        }
    }
    int IDmax=this->minerals_indx_to_ID.at(argmax);
    
    //find a worker mining it : 
    for (auto& worker : this->baseWorkers) {
        int ID = worker->getID();
        if (workerMineralTable.at(ID) == IDmax) {
            this->sendWorker(destBase, worker);
            return;
        }
    }
   

};


static bool isOnePos(std::vector<int> v) {
    for (int n : v) {
        if (n > 0) {
            return true;
        }
    }
;   return false;
}

static int sum(std::vector<int> v) {
    int n = 0;
    for (int k : v) {
        n += k;
    }
    return n;
}
void OwnedBase::dispatchWorkersToMe(std::vector<OwnedBase> ownedBases) {
    std::vector<int> workersToMoveCount;
    std::vector<OwnedBase> diffBases;
    std::vector<int> Alphas;

    float maxDist = 2000;

    for (auto& base : ownedBases) {
        float dist = base.pos.getDistance(this->pos);
        if(dist >0 && dist < maxDist){
            workersToMoveCount.push_back(0);
            diffBases.push_back(base);
            Alphas.push_back(base.baseWorkers.size() - 2 * base.mineralsOccupancyTable.size());

        }
    }
    //Alpha = workers-2*Patches
    //if alpha>0 : their is saturation.

    int myAlpha = this->baseWorkers.size() - 2 * this->mineralsOccupancyTable.size();;

    
    while (sum(workersToMoveCount) <= 6 && myAlpha < 0 && isOnePos(Alphas)) {
        for (int i = 0; i < diffBases.size(); i++) {
            if (Alphas.at(i) > 0) {
                //order a move
                diffBases.at(i).sendSomeone(this);
                //check update coeffs;
                Alphas.at(i)--;
                myAlpha++;
                workersToMoveCount.at(i)++;
                break;
            }
        }
    }
    
};
