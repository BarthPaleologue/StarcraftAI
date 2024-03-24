#pragma once
#include "BT_DECO_SQUAD_CONDITION.h"

class BT_DECO_CONDITION_SQUAD_COOLING_DOWN
	: public BT_DECO_SQUAD_CONDITION
{
public:
	BT_DECO_CONDITION_SQUAD_COOLING_DOWN(std::string name, Squad* squad, BT_NODE* parent);
	std::string GetDescription() override;

	static bool IsCoolingDown(Squad* squad, void* data);
};

