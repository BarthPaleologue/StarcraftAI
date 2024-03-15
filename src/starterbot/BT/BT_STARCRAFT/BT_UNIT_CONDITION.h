#pragma once
#include "BT_NODE.h"
#include <BWAPI.h>

class BT_UNIT_CONDITION :
	public BT_NODE
{
public:
	typedef bool(*CONDITION_CBK)(BWAPI::Unit unit, void* data);
protected:
	CONDITION_CBK  ConditionCBK;
	BWAPI::Unit    m_unit;

public:
	BT_UNIT_CONDITION(std::string name, BWAPI::Unit unit, BT_NODE* parent, CONDITION_CBK conditionCBK);
	State Evaluate(void* data) override;
	std::string GetDescription() override;
};

