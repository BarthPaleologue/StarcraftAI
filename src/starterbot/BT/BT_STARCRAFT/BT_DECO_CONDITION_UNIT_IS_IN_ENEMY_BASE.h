#pragma once
#include "BT_DECO_UNIT_CONDITION.h"
class BT_DECO_CONDITION_UNIT_IS_IN_ENEMY_BASE :
    public BT_DECO_UNIT_CONDITION
{
public:
		BT_DECO_CONDITION_UNIT_IS_IN_ENEMY_BASE(std::string name, BWAPI::Unit unit, BT_NODE* parent);
		std::string GetDescription() override;

		static bool IsInEnemyBase(BWAPI::Unit unit, void* data);
};

