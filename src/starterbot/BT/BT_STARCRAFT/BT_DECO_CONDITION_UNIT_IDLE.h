#pragma once
#include "BT_DECO_UNIT_CONDITION.h"
#include <BWAPI.h>

class BT_DECO_CONDITION_UNIT_IDLE :
    public BT_DECO_UNIT_CONDITION
{
public:
    BT_DECO_CONDITION_UNIT_IDLE(std::string name, BWAPI::Unit unit, BT_NODE* parent);
    std::string GetDescription() override;

    static bool IsIdle(BWAPI::Unit unit, void* data);
};

