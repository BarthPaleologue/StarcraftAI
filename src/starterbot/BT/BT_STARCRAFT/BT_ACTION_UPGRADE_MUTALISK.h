#pragma once
#include "BT_ACTION.h"
class BT_ACTION_UPGRADE_MUTALISK :
    public BT_ACTION
{
public:
    BT_ACTION_UPGRADE_MUTALISK(std::string name, BT_NODE* parent);
private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    BT_NODE::State ChooseUpgrade(void* data);
};

