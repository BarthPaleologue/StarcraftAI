#include "BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS.h"
#include "Tools.h"
#include "Blackboard.h"

BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS::BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS::Evaluate(void* data)
{
    return ReturnState(SendIdleWorkerToMinerals(data));
}

std::string BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS::GetDescription()
{
    return "SEND IDLE WORKER TO MINERAL";
}


BT_NODE::State BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS::SendIdleWorkerToMinerals(void* data)
{
    Blackboard* pData = (Blackboard*)data;
    const BWAPI::Unitset& myUnits = BWAPI::Broodwar->self()->getUnits();
    for (auto& unit : myUnits)
    {
        // Check the unit type, if it is an idle worker, then we want to send it somewhere
//        std::cout<<unit->getType().isWorker()<<std::endl;
        if (unit->getType().isWorker() && unit->isIdle())
        {   
            std::vector<int> table = pData->mineralsOccupancyTable;
            //find min:
            int min = table.at(0);
            int min_id = 0;
            for (int i = 0; i < table.size(); i++) {
                if (table.at(i) < min) {
                    min = table.at(i);
                    min_id = i;
                }
            }
            int mineralID = pData->minerals_indx_to_ID.at(min_id);
     
            BWAPI::Unit mineralTarget = Tools::GetUnitById(mineralID,BWAPI::Broodwar->getMinerals());
            unit->rightClick(mineralTarget);
            pData->unitsFarmingMinerals.insert(unit);
            pData->mineralsOccupancyTable.at(min_id)++;
            return BT_NODE::SUCCESS;

        }
    }

    return BT_NODE::FAILURE;
}