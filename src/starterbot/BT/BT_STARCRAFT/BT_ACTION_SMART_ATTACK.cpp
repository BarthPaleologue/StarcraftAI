#include "BT_ACTION_SMART_ATTACK.h"
#include "Tools.h"
#include "targeting/ForceTools.h"
#include "Blackboard.h"

BT_ACTION_SMART_ATTACK::BT_ACTION_SMART_ATTACK(std::string name, BWAPI::Unit unit, BT_NODE* parent)
	: BT_ACTION(name, parent), m_unit(unit) {}

BT_NODE::State BT_ACTION_SMART_ATTACK::Evaluate(void* data)
{
	return ReturnState(SmartAttack(data));
}

std::string BT_ACTION_SMART_ATTACK::GetDescription()
{
	return "GO TO ENEMY BASE";
}

BT_NODE::State BT_ACTION_SMART_ATTACK::SmartAttack(void* data)
{
	Blackboard* blackboard = (Blackboard*)data;

	BWAPI::Unitset enemyUnitsInRadius = Tools::GetUnitsInRadius(m_unit->getPosition(), 500, BWAPI::Broodwar->enemy()->getUnits());

	// check if an enemy can be one shotted
	for (auto& enemyUnit : enemyUnitsInRadius)
	{
		int dammage = BWAPI::Broodwar->getDamageFrom(m_unit->getType(), enemyUnit->getType(), BWAPI::Broodwar->self(), BWAPI::Broodwar->enemy());

		if (dammage < enemyUnit->getHitPoints()) continue;

		m_unit->attack(enemyUnit);
		return BT_NODE::SUCCESS;
	}

	// destroy buildings by priority
	/* TODO(Barth)
	* 
	zerg:
	zergling
	sunken colony
	sunken colony that's being morphed
	drone attacking zerglings
	spawning pool (morphed or not)
	drones

	protoss:
	photon cannon that's built
	photon cannon that's being built
	probe attacking zerglings
	zealot attacking zerglings
	pylons
	probes

	terran if no bunker built:
	scv building bunker
	scv building barracks
	scv attacking zerglings
	marine attacking zergling
	barracks (check if it's on the ground btw)
	SCV
	supply depot
	other GROUND units (not possible to kill floating buildings)

	terran if bunker built (not prio):
	marine (absolutely crucial)
	SCV attacking zerglings
	SCV repairing bunker
	bunker
	(afterwards returns to "no bunker")

	*/

	std::vector<BWAPI::UnitType> priorityBuildings;
	switch (blackboard->enemyRace)
	{
	case BWAPI::Races::Zerg:
		priorityBuildings.push_back(BWAPI::UnitTypes::Zerg_Zergling);
		priorityBuildings.push_back(BWAPI::UnitTypes::Zerg_Sunken_Colony);
		priorityBuildings.push_back(BWAPI::UnitTypes::Zerg_Spawning_Pool);
		priorityBuildings.push_back(BWAPI::UnitTypes::Zerg_Drone);
	case BWAPI::Races::Protoss:
		priorityBuildings.push_back(BWAPI::UnitTypes::Protoss_Photon_Cannon);
		priorityBuildings.push_back(BWAPI::UnitTypes::Protoss_Probe);
		priorityBuildings.push_back(BWAPI::UnitTypes::Protoss_Pylon);
	case BWAPI::Races::Terran:
		priorityBuildings.push_back(BWAPI::UnitTypes::Terran_SCV);
		priorityBuildings.push_back(BWAPI::UnitTypes::Terran_Supply_Depot);
	default:
		break;
	}

	// assign a score to each enemy unit based on the priority
	std::map<BWAPI::Unit, float> enemyUnitsScores;
	for (auto& enemyUnit : enemyUnitsInRadius)
	{
		float score = 0;
		for (int i = 0; i < priorityBuildings.size(); i++)
		{
			BWAPI::UnitType priorityBuilding = priorityBuildings[i];
			if (enemyUnit->getType() == priorityBuilding)
			{
				score = std::max(score, 1.0f / ((float)i + 1.0f));
				break;
			}
		}

		// the enemy unit is not a priority
		if (score == 0) continue;

		enemyUnitsScores[enemyUnit] = score;
	}

	// sort the scores to get the best target
	std::vector<std::pair<BWAPI::Unit, float>> sortedScores(enemyUnitsScores.begin(), enemyUnitsScores.end());
	std::sort(sortedScores.begin(), sortedScores.end(), [](const std::pair<BWAPI::Unit, float>& left, const std::pair<BWAPI::Unit, float>& right) {
		return left.second > right.second;
	});

	// attack the best target
	if (!sortedScores.empty())
	{
		m_unit->attack(sortedScores[0].first);
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
		return BT_NODE::SUCCESS;
	}

	// there is no enemy in range
	return BT_NODE::FAILURE;
}