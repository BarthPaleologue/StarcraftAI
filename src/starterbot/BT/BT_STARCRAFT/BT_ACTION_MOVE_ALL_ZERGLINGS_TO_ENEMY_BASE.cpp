#include "BT_ACTION_MOVE_ALL_ZERGLINGS_TO_ENEMY_BASE.h"
#include "Tools.h"
#include "Blackboard.h"

BT_ACTION_MOVE_ALL_ZERGLINGS_TO_ENEMY_BASE::BT_ACTION_MOVE_ALL_ZERGLINGS_TO_ENEMY_BASE(std::string name, BT_NODE* parent)
	: BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_MOVE_ALL_ZERGLINGS_TO_ENEMY_BASE::Evaluate(void* data)
{
	return ReturnState(GoToEnnemyBase(data));
}

std::string BT_ACTION_MOVE_ALL_ZERGLINGS_TO_ENEMY_BASE::GetDescription()
{
	return "ALL ZERGLINGS GO TO ENNEMY BASE";
}

BT_NODE::State BT_ACTION_MOVE_ALL_ZERGLINGS_TO_ENEMY_BASE::GoToEnnemyBase(void* data)
{
	Blackboard* blackboard = (Blackboard*)data;

	if (!blackboard->enemyBasesPositions.empty()) {
<<<<<<< HEAD
		// we found at least one enemy base
=======
		// we found at least one ennemy base
>>>>>>> 536c604732adac79e8b50b2dd35e36c4d7565363
		BWAPI::Position tilePosition = blackboard->enemyBasesPositions[0];

		std::vector<BWAPI::Unit> zerglings;
		Tools::GetAllUnitsOfType(BWAPI::UnitTypes::Zerg_Zergling, zerglings);

		for (auto zergling : zerglings) {
			zergling->move(tilePosition);
		}

		return BT_NODE::SUCCESS;
	}

	return BT_NODE::FAILURE;
}