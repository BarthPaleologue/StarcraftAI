#include "BT_DECO_CONDITION_BUILD_ORDER_FINISHED.h"

#include "Blackboard.h"
#include <BWAPI.h>
#include "Tools.h"

BT_DECO_CONDITION_BUILD_ORDER_FINISHED::BT_DECO_CONDITION_BUILD_ORDER_FINISHED(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, IsBuildOrderFinished) {}


std::string BT_DECO_CONDITION_BUILD_ORDER_FINISHED::GetDescription()
{
    return "DECO_CONDITION_BUILD_ORDER_FINISHED";
}

bool BT_DECO_CONDITION_BUILD_ORDER_FINISHED::IsBuildOrderFinished(void* data)
{
    Blackboard* blackboard = (Blackboard*)data;
    return blackboard->buildOrder.isFinished();
}
