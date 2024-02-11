#include <BT_COND_NOTHING_REQUESTED.h>
#include "Blackboard.h"
#include <iostream>

BT_COND_NOTHING_REQUESTED::BT_COND_NOTHING_REQUESTED(std::string name, BT_NODE* parent): 
    BT_CONDITION(name, parent, 0) { // TODO: use isNothingRequested directly
    
}

BT_NODE::State BT_COND_NOTHING_REQUESTED::Evaluate(void* data) {
    return (isNothingRequested(data)) ? Success() : Failure();
}

std::string BT_COND_NOTHING_REQUESTED::GetDescription()
{
    return "COND_NOTHING_REQUESTED";
}

bool BT_COND_NOTHING_REQUESTED::isNothingRequested(void* data) {
    Blackboard* blackboard = (Blackboard*)data;
    std::cout << blackboard->unitsRequested.size() << ' ' << blackboard->techsRequested.size() << std::endl;
    return blackboard->techsRequested.empty() && blackboard->unitsRequested.empty();
}