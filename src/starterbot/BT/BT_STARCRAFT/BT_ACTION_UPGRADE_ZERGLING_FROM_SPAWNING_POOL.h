#pragma once
#include "BT_ACTION.h"
class BT_ACTION_UPGRADE_ZERGLING_FROM_SPAWNING_POOL :
    public BT_ACTION
{
public:
    BT_ACTION_UPGRADE_ZERGLING_FROM_SPAWNING_POOL(std::string name, BT_NODE* parent);
private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    BT_NODE::State ChooseUpgrade(void* data);
};

