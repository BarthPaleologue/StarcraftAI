#pragma once
#include "BWAPI.h"
#include "targeting/Squad.h"

class HarassmentManager
{
public:
	HarassmentManager();
	~HarassmentManager() = default;

	int getTargetPriority(BWAPI::Unit attackingUnit, BWAPI::Unit enemyUnit, BWAPI::Race enemyRace);

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

	typedef std::vector<std::function<bool(Squad squad, BWAPI::Unit enemyUnit)>> PrioritySquadList;

	PrioritySquadList m_MutaliskSquadProtoss{};

	int evaluateMutaliskSquadPriority(Squad squad, BWAPI::Unit enemyUnit);
};