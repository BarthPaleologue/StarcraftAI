#pragma once
#include "BT_DECORATOR.h"
#include <BWAPI.h>

class BT_DECO_UNIT_CONDITION :
    public BT_DECORATOR
{
public:
    typedef bool(*CONDITION_CBK)(BWAPI::Unit unit, void* data);
protected:
    CONDITION_CBK  ConditionCBK;
	BWAPI::Unit    m_unit;

public:
    BT_DECO_UNIT_CONDITION(std::string name, BT_NODE* parent, BWAPI::Unit unit, CONDITION_CBK conditionCBK);
    State Evaluate(void* data) override;
    std::string GetDescription() override;
};

