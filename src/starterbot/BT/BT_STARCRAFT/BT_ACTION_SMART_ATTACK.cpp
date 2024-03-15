#include "BT_ACTION_SMART_ATTACK.h"
#include "Tools.h"
#include "targeting/ForceTools.h"
#include "targeting/TargetingTools.h"
#include "Blackboard.h"

BT_ACTION_SMART_ATTACK::BT_ACTION_SMART_ATTACK(std::string name, BWAPI::Unit unit, BT_NODE* parent)
	: BT_ACTION(name, parent), m_unit(unit) {}

BT_NODE::State BT_ACTION_SMART_ATTACK::Evaluate(void* data)
{
	return ReturnState(SmartAttack(data));
}

std::string BT_ACTION_SMART_ATTACK::GetDescription()
{
	return "ACTION_SMART_ATTACK";
}

BT_NODE::State BT_ACTION_SMART_ATTACK::SmartAttack(void* data)
{
	//std::cout << "SMART_ATTACK" << std::endl;

	Blackboard* blackboard = (Blackboard*)data;

	BWAPI::Unitset enemyUnitsInRadius = BWAPI::Broodwar->enemy()->getUnits(); //Tools::GetUnitsInRadius(m_unit->getPosition(), 400, BWAPI::Broodwar->enemy()->getUnits());

	// check if an enemy can be one shotted
	for (auto& enemyUnit : enemyUnitsInRadius)
	{
		int dammage = BWAPI::Broodwar->getDamageFrom(m_unit->getType(), enemyUnit->getType(), BWAPI::Broodwar->self(), BWAPI::Broodwar->enemy());

		if (dammage < enemyUnit->getHitPoints()) continue;

		m_unit->attack(enemyUnit);
		//std::cout << "one shotting " << enemyUnit->getType().c_str() << std::endl;
		return BT_NODE::SUCCESS;
	}

	// destroy priority buildings
	// assign a score to each enemy unit based on the priority
	std::map<BWAPI::Unit, int> enemyUnitsScores;
	for (auto& enemyUnit : enemyUnitsInRadius)
	{
		int score = TargetingTools::LOWEST_PRIORITY;

		switch (blackboard->enemyRace)
		{
		case BWAPI::Races::Protoss:
			score = TargetingTools::enemyProtossPriorityScore(enemyUnit);
			break;
		case BWAPI::Races::Terran:
			score = TargetingTools::enemyTerranPriorityScore(enemyUnit);
			break;
		case BWAPI::Races::Zerg:
			score = TargetingTools::enemyZergPriorityScore(enemyUnit);
			break;
		default:
			break;
		}

		// the enemy unit is not a priority
		if (score == TargetingTools::LOWEST_PRIORITY) continue;

		enemyUnitsScores[enemyUnit] = score;
	}

	// sort the scores to get the best target
	std::vector<std::pair<BWAPI::Unit, int>> sortedScores(enemyUnitsScores.begin(), enemyUnitsScores.end());
	std::sort(sortedScores.begin(), sortedScores.end(), [](const std::pair<BWAPI::Unit, int>& left, const std::pair<BWAPI::Unit, int>& right) {
		return left.second > right.second;
	});

	// attack the best target
	if (!sortedScores.empty())
	{
		m_unit->attack(sortedScores[0].first);
		//std::cout << "priority attacking " << sortedScores[0].first->getType().c_str() << std::endl;
		return BT_NODE::SUCCESS;
	}

	// there was no priority target, attack the closest enemy
	BWAPI::Unit closestEnemy = nullptr;
	int closestDistance = INT_MAX;
	for (auto& enemyUnit : enemyUnitsInRadius)
	{
		int distance = m_unit->getDistance(enemyUnit);
		if (distance >= closestDistance) continue;
		
		closestDistance = distance;
		closestEnemy = enemyUnit;
	}

	if (closestEnemy != nullptr)
	{
		m_unit->attack(closestEnemy);
		//std::cout << "closest attacking " << closestEnemy->getType().c_str() << std::endl;
		return BT_NODE::SUCCESS;
	}

	//std::cout << "attacking nothing" << std::endl;

	// there is no enemy in range
	return BT_NODE::FAILURE;
}