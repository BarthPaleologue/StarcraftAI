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
    BT_NODE::State result = BT_NODE::FAILURE;
    for (auto& base : pData->ownedBases)
    {
        
        BT_NODE::State my_state = base.base_SendIdleWorkerToMinerals();
        if (my_state==BT_NODE::SUCCESS) {
            result = BT_NODE::SUCCESS;
        }
    }
    return result;
}