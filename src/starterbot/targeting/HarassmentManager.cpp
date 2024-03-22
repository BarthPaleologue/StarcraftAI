#include "TargetPriority.h"

HarassmentManager::HarassmentManager()
{
	// 4 Pool vs Protoss
	m_EarlyProtoss.push_back([](BWAPI::Unit unit) {
		return unit->getType() == BWAPI::UnitTypes::Protoss_Photon_Cannon;
	});
	m_EarlyProtoss.push_back([](BWAPI::Unit unit) {
		return unit->getType() == BWAPI::UnitTypes::Protoss_Probe && unit->isAttacking();
	});
	m_EarlyProtoss.push_back([](BWAPI::Unit unit) {
		return unit->getType() == BWAPI::UnitTypes::Protoss_Zealot && unit->isAttacking();
	});
	m_EarlyProtoss.push_back([](BWAPI::Unit unit) {
		return unit->getType() == BWAPI::UnitTypes::Protoss_Pylon;
	});
	m_EarlyProtoss.push_back([](BWAPI::Unit unit) {
		return unit->getType() == BWAPI::UnitTypes::Protoss_Gateway;
	});

	// 4 Pool vs Zerg
	m_EarlyZerg.push_back([](BWAPI::Unit unit) {
		return unit->getType() == BWAPI::UnitTypes::Zerg_Zergling;
	});
	m_EarlyZerg.push_back([](BWAPI::Unit unit) {
		return unit->getType() == BWAPI::UnitTypes::Zerg_Sunken_Colony;
	});
	m_EarlyZerg.push_back([](BWAPI::Unit unit) {
		return unit->getType() == BWAPI::UnitTypes::Zerg_Drone && unit->isAttacking();
	});
	m_EarlyZerg.push_back([](BWAPI::Unit unit) {
		return unit->getType() == BWAPI::UnitTypes::Zerg_Spawning_Pool;
	});
	m_EarlyZerg.push_back([](BWAPI::Unit unit) {
		return unit->getType() == BWAPI::UnitTypes::Zerg_Drone;
	});

	// 4 Pool vs Terran (without Bunker)
	m_EarlyTerranNoBunker.push_back([](BWAPI::Unit unit) {
		return unit->getType() == BWAPI::UnitTypes::Terran_SCV && unit->isConstructing() && unit->getBuildType() == BWAPI::UnitTypes::Terran_Bunker;
	});
	m_EarlyTerranNoBunker.push_back([](BWAPI::Unit unit) {
		return unit->getType() == BWAPI::UnitTypes::Terran_SCV && unit->isConstructing() && unit->getBuildType() == BWAPI::UnitTypes::Terran_Barracks;
	});
	m_EarlyTerranNoBunker.push_back([](BWAPI::Unit unit) {
		return unit->getType() == BWAPI::UnitTypes::Terran_SCV && unit->isAttacking();
	});
	m_EarlyTerranNoBunker.push_back([](BWAPI::Unit unit) {
		return unit->getType() == BWAPI::UnitTypes::Terran_Marine && unit->isAttacking();
	});
	m_EarlyTerranNoBunker.push_back([](BWAPI::Unit unit) {
		return unit->getType() == BWAPI::UnitTypes::Terran_Barracks && unit->isCompleted() && !unit->isLifted();
	});
	m_EarlyTerranNoBunker.push_back([](BWAPI::Unit unit) {
		return unit->getType() == BWAPI::UnitTypes::Terran_SCV;
	});
	m_EarlyTerranNoBunker.push_back([](BWAPI::Unit unit) {
		return unit->getType() == BWAPI::UnitTypes::Terran_Supply_Depot;
	});
	m_EarlyTerranNoBunker.push_back([](BWAPI::Unit unit) {
		return unit->getType().isBuilding();
	});

	// 4 Pool vs Terran (with Bunker)
	m_EarlyTerranWithBunker.push_back([](BWAPI::Unit unit) {
		return unit->getType() == BWAPI::UnitTypes::Terran_Marine;
	});
	m_EarlyTerranWithBunker.push_back([](BWAPI::Unit unit) {
		return unit->getType() == BWAPI::UnitTypes::Terran_SCV && unit->isAttacking();
	});
	m_EarlyTerranWithBunker.push_back([](BWAPI::Unit unit) {
		return unit->getType() == BWAPI::UnitTypes::Terran_SCV && unit->isRepairing();
	});
	m_EarlyTerranWithBunker.push_back([](BWAPI::Unit unit) {
		return unit->getType() == BWAPI::UnitTypes::Terran_Bunker;
	});
}

int HarassmentManager::LOWEST_PRIORITY = -10000;

int HarassmentManager::getTargetPriority(BWAPI::Unit unit, BWAPI::Race enemyRace)
{
	computePriorityList(enemyRace);
	return evaluatePriority(unit, *m_currentPriorityList);
}

void HarassmentManager::computePriorityList(BWAPI::Race enemyRace)
{
	if (enemyRace == BWAPI::Races::Protoss) {
		m_currentPriorityList = &m_EarlyProtoss;
		return;
	} 

	if (enemyRace == BWAPI::Races::Zerg) {
		m_currentPriorityList = &m_EarlyZerg;
		return;
	}

	// Terran if there is a bunker
	bool hasBunker = false;	
	for (auto& unit : BWAPI::Broodwar->enemy()->getUnits()) {
		if (unit->getType() == BWAPI::UnitTypes::Terran_Bunker) {
			hasBunker = true;
			break;
		}
	}

	if (hasBunker) {
		m_currentPriorityList = &m_EarlyTerranWithBunker;
	}
	else {
		m_currentPriorityList = &m_EarlyTerranNoBunker;
	}
}

int HarassmentManager::evaluatePriority(BWAPI::Unit unit, std::vector<std::function<bool(BWAPI::Unit)>>& priorityList)
{
	int score = 0;
	for (auto& matchPredicate : priorityList)
	{
		if (matchPredicate(unit)) return score;
		score--;
	}

	return -10000;
}
