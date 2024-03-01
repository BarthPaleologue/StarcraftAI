#include "BT_ACTION_GO_TO_ENEMY_BASE.h"
#include "Tools.h"
#include "Blackboard.h"

BT_ACTION_GO_TO_ENEMY_BASE::BT_ACTION_GO_TO_ENEMY_BASE(std::string name, BWAPI::Unit unit, BT_NODE* parent)
	: BT_ACTION(name, parent), m_unit(unit) {}

BT_NODE::State BT_ACTION_GO_TO_ENEMY_BASE::Evaluate(void* data)
{
	return ReturnState(GoToEnnemyBase(data));
}

std::string BT_ACTION_GO_TO_ENEMY_BASE::GetDescription()
{
	return "GO TO ENEMY BASE";
}

BT_NODE::State BT_ACTION_GO_TO_ENEMY_BASE::GoToEnnemyBase(void* data)
{
	Blackboard* blackboard = (Blackboard*)data;

	if (!blackboard->enemyBasesPositions.empty()) {
<<<<<<< HEAD
		// we found at least one enemy base
=======
		// we found at least one ennemy base
>>>>>>> 536c604732adac79e8b50b2dd35e36c4d7565363
		BWAPI::Position tilePosition = blackboard->enemyBasesPositions[0];

		m_unit->move(tilePosition);

		return BT_NODE::SUCCESS;
	}

	return BT_NODE::FAILURE;
}