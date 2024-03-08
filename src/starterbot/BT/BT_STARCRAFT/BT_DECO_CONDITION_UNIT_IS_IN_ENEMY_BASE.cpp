#include "BT_DECO_CONDITION_UNIT_IS_IN_ENEMY_BASE.h"
#include "Blackboard.h"

BT_DECO_CONDITION_UNIT_IS_IN_ENEMY_BASE::BT_DECO_CONDITION_UNIT_IS_IN_ENEMY_BASE(std::string name, BWAPI::Unit unit, BT_NODE* parent)
	:BT_DECO_UNIT_CONDITION(name, parent, unit, IsInEnemyBase)
{

}

std::string BT_DECO_CONDITION_UNIT_IS_IN_ENEMY_BASE::GetDescription()
{
	return "BT_DECO_CONDITION_UNIT_IDLE";
}

bool BT_DECO_CONDITION_UNIT_IS_IN_ENEMY_BASE::IsInEnemyBase(BWAPI::Unit unit, void* data)
{
	Blackboard* blackboard = (Blackboard*)data;

	for (auto& basePosition : blackboard->enemyBasesPositions)
	{
		if (unit->getDistance(basePosition) < 300)
		{
			return true;
		}
	}

	return false;
}

