#pragma once

#include "BT_CONDITION.h"
#include <cassert>
#include <format>

//--------------------
class BT_COND_NOTHING_REQUESTED : public BT_CONDITION {

public:
    BT_COND_NOTHING_REQUESTED(std::string name, BT_NODE* parent);
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    bool isNothingRequested(void* data);
};
//----------