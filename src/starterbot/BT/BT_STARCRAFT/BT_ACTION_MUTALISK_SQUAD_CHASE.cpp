#include "BT_ACTION_MUTALISK_SQUAD_CHASE.h"

BT_ACTION_MUTALISK_SQUAD_CHASE::BT_ACTION_MUTALISK_SQUAD_CHASE(std::string name, Squad squad, BT_NODE* parent)
	: BT_ACTION(name, parent), m_squad(squad)
{
}

BT_NODE::State BT_ACTION_MUTALISK_SQUAD_CHASE::Evaluate(void* data)
{
	return ReturnState(Chase(data));
}

std::string BT_ACTION_MUTALISK_SQUAD_CHASE::GetDescription()
{
	return "BT_ACTION_MUTALISK_SQUAD_CHASE";
}

BT_NODE::State BT_ACTION_MUTALISK_SQUAD_CHASE::Chase(void* data)
{
	// First try to chase the last target of the squad
	BWAPI::Unit squadLastTarget = m_squad.getLastTarget();
	if (squadLastTarget != nullptr) {
		m_squad.moveTo(squadLastTarget->getPosition());
		return BT_NODE::State::SUCCESS;
	}

	// Else chase the squad's closest enemy unit
	BWAPI::Unitset enemyUnits = m_squad.getEnemyUnitsInRadius(1000);
	if (enemyUnits.empty()) {
		return BT_NODE::State::FAILURE;
	}

	BWAPI::Unit closestEnemy = nullptr;
	int minDist = INT_MAX;
	for (auto& enemy : enemyUnits) {
		int dist = m_squad.getPosition().getDistance(enemy->getPosition());
		if (dist < minDist) {
			minDist = dist;
			closestEnemy = enemy;
		}
	}

	m_squad.moveTo(closestEnemy->getPosition());
	return BT_NODE::State::SUCCESS;
}
