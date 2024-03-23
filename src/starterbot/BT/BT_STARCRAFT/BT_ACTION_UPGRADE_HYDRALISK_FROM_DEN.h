#pragma once
#include "BT_ACTION.h"
class BT_ACTION_UPGRADE_HYDRALISK_FROM_DEN :
    public BT_ACTION
{
public:
    BT_ACTION_UPGRADE_HYDRALISK_FROM_DEN(std::string name, BT_NODE* parent) : BT_ACTION(name, parent) {}
private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    BT_NODE::State ChooseUpgrade(void* data);
};

