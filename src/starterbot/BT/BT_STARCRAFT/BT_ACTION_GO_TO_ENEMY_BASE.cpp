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

	if (blackboard->enemyBasesPositions.empty()) {
		return BT_NODE::FAILURE;
	}

	// we found at least one enemy base
	BWAPI::Position basePosition = blackboard->enemyBasesPositions[0];

	if (m_unit->getDistance(basePosition) < 700) {
		return BT_NODE::SUCCESS;
	}

	m_unit->move(basePosition);

	return BT_NODE::RUNNING;
}