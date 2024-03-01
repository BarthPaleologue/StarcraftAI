#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class BT_ACTION_BUILD_SUPPLY_PROVIDER: public BT_ACTION {
public:
    [[deprecated("Zergs can't 'build' an overlord")]]
    BT_ACTION_BUILD_SUPPLY_PROVIDER(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State BuildSupplyProvider(void* data);
};
//----------