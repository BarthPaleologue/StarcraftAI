#pragma once
#include "BT_DECO_SQUAD_CONDITION.h"

class BT_DECO_CONDITION_SQUAD_INVALID_TARGET
	:public BT_DECO_SQUAD_CONDITION
{
public:
	BT_DECO_CONDITION_SQUAD_INVALID_TARGET(std::string name, Squad* squad, BT_NODE* parent);
	std::string GetDescription() override;

	static bool IsTargetInvalid(Squad* squad, void* data);
};

