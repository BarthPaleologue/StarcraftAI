#include "HarassmentManager.h"
#include "ForceTools.h"

HarassmentManager::HarassmentManager()
{
	// Early vs Protoss
	m_EarlyProtoss.push_back([](BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit) {
		// check if we can one shot the unit
		return ForceTools::fightPredictor(1, attackingUnit->getType(), BWAPI::Broodwar->self(), 1, enemyUnit->getType(), BWAPI::Broodwar->enemy()).second < 0.01;
	});
	m_EarlyProtoss.push_back([](BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit) {
		return enemyUnit->getType() == BWAPI::UnitTypes::Protoss_Photon_Cannon;
	});
	m_EarlyProtoss.push_back([](BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit) {
		return enemyUnit->getType() == BWAPI::UnitTypes::Protoss_Probe && enemyUnit->isAttacking();
	});
	m_EarlyProtoss.push_back([](BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit) {
		return enemyUnit->getType() == BWAPI::UnitTypes::Protoss_Zealot && enemyUnit->isAttacking();
	});
	m_EarlyProtoss.push_back([](BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit) {
		return enemyUnit->getType() == BWAPI::UnitTypes::Protoss_Pylon;
	});
	m_EarlyProtoss.push_back([](BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit) {
		return enemyUnit->getType() == BWAPI::UnitTypes::Protoss_Gateway;
	});

	// Early vs Zerg
	m_EarlyZerg.push_back([](BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit) {
		// check if we can one shot the unit
		return ForceTools::fightPredictor(1, attackingUnit->getType(), BWAPI::Broodwar->self(), 1, enemyUnit->getType(), BWAPI::Broodwar->enemy()).second < 0.01;
		});
	m_EarlyZerg.push_back([](BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit) {
		return enemyUnit->getType() == BWAPI::UnitTypes::Zerg_Zergling;
	});
	m_EarlyZerg.push_back([](BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit) {
		return enemyUnit->getType() == BWAPI::UnitTypes::Zerg_Sunken_Colony;
	});
	m_EarlyZerg.push_back([](BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit) {
		return enemyUnit->getType() == BWAPI::UnitTypes::Zerg_Drone && enemyUnit->isAttacking();
	});
	m_EarlyZerg.push_back([](BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit) {
		return enemyUnit->getType() == BWAPI::UnitTypes::Zerg_Spawning_Pool;
	});
	m_EarlyZerg.push_back([](BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit) {
		return enemyUnit->getType() == BWAPI::UnitTypes::Zerg_Drone;
	});

	// Early vs Terran (without Bunker)
	m_EarlyTerranNoBunker.push_back([](BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit) {
		// check if we can one shot the unit
		return ForceTools::fightPredictor(1, attackingUnit->getType(), BWAPI::Broodwar->self(), 1, enemyUnit->getType(), BWAPI::Broodwar->enemy()).second < 0.01;
		});
	m_EarlyTerranNoBunker.push_back([](BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit) {
		return enemyUnit->getType() == BWAPI::UnitTypes::Terran_SCV && enemyUnit->isConstructing() && enemyUnit->getBuildType() == BWAPI::UnitTypes::Terran_Bunker;
	});
	m_EarlyTerranNoBunker.push_back([](BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit) {
		return enemyUnit->getType() == BWAPI::UnitTypes::Terran_SCV && enemyUnit->isConstructing() && enemyUnit->getBuildType() == BWAPI::UnitTypes::Terran_Barracks;
	});
	m_EarlyTerranNoBunker.push_back([](BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit) {
		return enemyUnit->getType() == BWAPI::UnitTypes::Terran_SCV && enemyUnit->isAttacking();
	});
	m_EarlyTerranNoBunker.push_back([](BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit) {
		return enemyUnit->getType() == BWAPI::UnitTypes::Terran_Marine && enemyUnit->isAttacking();
	});
	m_EarlyTerranNoBunker.push_back([](BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit) {
		return enemyUnit->getType() == BWAPI::UnitTypes::Terran_Barracks && enemyUnit->isCompleted() && !enemyUnit->isLifted();
	});
	m_EarlyTerranNoBunker.push_back([](BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit) {
		return enemyUnit->getType() == BWAPI::UnitTypes::Terran_SCV;
	});
	m_EarlyTerranNoBunker.push_back([](BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit) {
		return enemyUnit->getType() == BWAPI::UnitTypes::Terran_Supply_Depot;
	});
	m_EarlyTerranNoBunker.push_back([](BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit) {
		return enemyUnit->getType().isBuilding();
	});

	// Early vs Terran (with Bunker)
	m_EarlyTerranWithBunker.push_back([](BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit) {
		// check if we can one shot the unit
		return ForceTools::fightPredictor(1, attackingUnit->getType(), BWAPI::Broodwar->self(), 1, enemyUnit->getType(), BWAPI::Broodwar->enemy()).second < 0.01;
	});
	m_EarlyTerranWithBunker.push_back([](BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit) {
		return enemyUnit->getType() == BWAPI::UnitTypes::Terran_Marine;
	});
	m_EarlyTerranWithBunker.push_back([](BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit) {
		return enemyUnit->getType() == BWAPI::UnitTypes::Terran_SCV && enemyUnit->isAttacking();
	});
	m_EarlyTerranWithBunker.push_back([](BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit) {
		return enemyUnit->getType() == BWAPI::UnitTypes::Terran_SCV && enemyUnit->isRepairing();
	});
	m_EarlyTerranWithBunker.push_back([](BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit) {
		return enemyUnit->getType() == BWAPI::UnitTypes::Terran_Bunker;
	});

	// Mutalisk vs Protoss
	m_MutaliskSquadProtoss.push_back([](Squad*, BWAPI::Unit enemyUnit) {
		return enemyUnit->getType() == BWAPI::UnitTypes::Protoss_Photon_Cannon;
	});
	m_MutaliskSquadProtoss.push_back([](Squad*, BWAPI::Unit enemyUnit) {
		return enemyUnit->getType() == BWAPI::UnitTypes::Protoss_Probe;
	});
	m_MutaliskSquadProtoss.push_back([](Squad*, BWAPI::Unit enemyUnit) {
		// any anti-air unit
		return enemyUnit->getType().airWeapon() != BWAPI::WeaponTypes::None;
	});
	m_MutaliskSquadProtoss.push_back([](Squad* squad, BWAPI::Unit enemyUnit) {
		// units that can be one-shotted withtout taking too much damage
		std::pair<float, float> prediction = ForceTools::fightPredictor(squad->getNbUnits(), BWAPI::UnitTypes::Zerg_Mutalisk, BWAPI::Broodwar->self(), 1, enemyUnit->getType(), BWAPI::Broodwar->enemy());
		return prediction.second <= 0.01 && prediction.first > 0.9 * (double)squad->getNbUnits();
	});
}

int HarassmentManager::LOWEST_PRIORITY = -10000;

int HarassmentManager::getTargetPriority(BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit, BWAPI::Race enemyRace)
{
	computePriorityList(enemyRace);
	return evaluatePriority(attackingUnit, enemyUnit, *m_currentPriorityList);
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
	for (auto& enemyUnit : BWAPI::Broodwar->enemy()->getUnits()) {
		if (enemyUnit->getType() == BWAPI::UnitTypes::Terran_Bunker) {
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

int HarassmentManager::evaluatePriority(BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit, PriorityList& priorityList)
{
	int score = 0;
	for (auto& matchPredicate : priorityList)
	{
		if (matchPredicate(attackingUnit, enemyUnit)) return score;
		score--;
	}

	return LOWEST_PRIORITY;
}

int HarassmentManager::getSquadTargetPriority(Squad* squad, BWAPI::Unit enemyUnit)
{
	int score = 0;
	for (auto& matchPredicate : m_MutaliskSquadProtoss)
	{
		if (matchPredicate(squad, enemyUnit)) return score;
		score--;
	}

	return LOWEST_PRIORITY;
}
