#pragma once
#include "BT_ACTION.h"
class BT_ACTION_UPGRADE_HYDRALISK_FROM_EVOLUTION_CHAMBER :
    public BT_ACTION
{
public:
    BT_ACTION_UPGRADE_HYDRALISK_FROM_EVOLUTION_CHAMBER(std::string name, BT_NODE* parent) : BT_ACTION(name, parent) {};
private:
    BT_NODE::State Evaluate(void* data) override;
    std::string GetDescription() override;
    BT_NODE::State ChooseUpgrade(void* data);
};

