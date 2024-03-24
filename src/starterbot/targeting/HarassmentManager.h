#pragma once
#include "BWAPI.h"
#include "targeting/Squad.h"

/// <summary>
/// The goal of the harassment manager is to help units and squad to find suitable targets when harassing the enemy.
/// The information is provided through a per-enemy priority. The squad or unit can then choose base on the provided priority scores.
/// </summary>
class HarassmentManager
{
public:
	HarassmentManager();
	~HarassmentManager() = default;

	int getTargetPriority(BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit, BWAPI::Race enemyRace);

	int getSquadTargetPriority(Squad* squad, BWAPI::Unit enemyUnit);

	static int LOWEST_PRIORITY;

private:
	typedef std::vector<std::function<bool(BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit)>> PriorityList;

	PriorityList m_EarlyTerranNoBunker{};
	PriorityList m_EarlyTerranWithBunker{};
	PriorityList m_EarlyProtoss{};
	PriorityList m_EarlyZerg{};

	PriorityList* m_currentPriorityList{};

	void computePriorityList(BWAPI::Race enemyRace);

	int evaluatePriority(BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit, PriorityList &priorityList);

	typedef std::vector<std::function<bool(Squad* squad, BWAPI::Unit enemyUnit)>> PrioritySquadList;

	PrioritySquadList m_MutaliskSquadProtoss{};
};