#pragma once
#include "BT.h"
#include "BWAPI.h"

class BT_DECO_CONDITION_NOT_ENOUGH_UNIT: public BT_DECO_CONDITION
{
public:
	BT_DECO_CONDITION_NOT_ENOUGH_UNIT(std::string name, BT_NODE* parent, BWAPI::UnitType unitType, int minAmount);
	std::string GetDescription() override;
	State Evaluate(void* data) override;

private:
	BWAPI::UnitType m_unitTypeConcerned;
	int m_minAmount;
};