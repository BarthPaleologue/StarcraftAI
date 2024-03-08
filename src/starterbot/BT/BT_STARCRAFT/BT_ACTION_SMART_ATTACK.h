#pragma once
#include "BT_ACTION.h"
#include <BWAPI.h>

class BT_ACTION_SMART_ATTACK :
    public BT_ACTION
{
public:
	BT_ACTION_SMART_ATTACK(std::string name, BWAPI::Unit unit, BT_NODE* parent);

private:
	BT_NODE::State Evaluate(void* data) override;
	std::string GetDescription() override;
	BT_NODE::State SmartAttack(void* data);

	BWAPI::Unit m_unit;
};

