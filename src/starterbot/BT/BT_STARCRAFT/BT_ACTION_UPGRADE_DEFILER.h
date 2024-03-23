#pragma once
#include "BT_ACTION.h"
class BT_ACTION_UPGRADE_DEFILER :
    public BT_ACTION
{
public:
    BT_ACTION_UPGRADE_DEFILER(std::string name, BT_NODE* parent);
private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    BT_NODE::State ChooseUpgrade(void* data);
};
