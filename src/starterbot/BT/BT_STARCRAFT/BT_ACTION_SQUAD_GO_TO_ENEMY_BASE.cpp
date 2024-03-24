#include "BT_ACTION_SQUAD_GO_TO_ENEMY_BASE.h"
#include "Blackboard.h"

BT_ACTION_SQUAD_GO_TO_ENEMY_BASE::BT_ACTION_SQUAD_GO_TO_ENEMY_BASE(std::string name, Squad* squad, BT_NODE* parent)
	: BT_ACTION(name, parent), m_squad(squad)
{
}

BT_NODE::State BT_ACTION_SQUAD_GO_TO_ENEMY_BASE::Evaluate(void* data)
{
    return ReturnState(GoToEnemyBase(data));
}

std::string BT_ACTION_SQUAD_GO_TO_ENEMY_BASE::GetDescription()
{
    return "BT_ACTION_SQUAD_GO_TO_ENEMY_BASE";
}

BT_NODE::State BT_ACTION_SQUAD_GO_TO_ENEMY_BASE::GoToEnemyBase(void* data)
{
	Blackboard* blackboard = (Blackboard*)data;

	if (blackboard->enemyBasesPositions.empty()) {
		return BT_NODE::FAILURE;
	}

	// we found at least one enemy base
	BWAPI::Position basePosition = blackboard->enemyBasesPositions[0];

	if (m_squad->getPosition().getDistance(basePosition) < 400) {
		return BT_NODE::SUCCESS;
	}

	m_squad->moveTo(basePosition);

	return BT_NODE::SUCCESS;
}
