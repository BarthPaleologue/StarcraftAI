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
	return "GO TO ENNEMY BASE";
}

BT_NODE::State BT_ACTION_GO_TO_ENEMY_BASE::GoToEnnemyBase(void* data)
{
	Blackboard* blackboard = (Blackboard*)data;

	if (!blackboard->enemyBasesPositions.empty()) {
		// we found at least one enemy base
		BWAPI::Position tilePosition = blackboard->enemyBasesPositions[0];

		m_unit->move(tilePosition);

		return BT_NODE::SUCCESS;
	}

	return BT_NODE::FAILURE;
}