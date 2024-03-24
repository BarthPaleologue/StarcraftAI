#pragma once
#include <cassert>
#include "BT_CONDITION.h"


// Specific conditional task implementing the following condition: "a value is lesser than a constant threshold" 
// The Value reference and the Threshold constant are passed to the constructor

// Reminder of the definition of a conditional node
//Evaluates the specified conditional task. If the conditional task returns true then return success, else return failure
// no running state 
//--------------------
template <class T> class BT_COND_LESSER_THAN : public BT_CONDITION {

protected:
    T Threshold;
    T& ValueRef;
    bool StrictComparison;
public:
    BT_COND_LESSER_THAN(std::string name, BT_NODE* parent,T threshold,T& ValueRef,bool strictComparison);
    State Evaluate(void* data) override;
    std::string GetDescription() override;
};
//----------


