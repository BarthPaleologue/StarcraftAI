#pragma once
#include "BWAPI.h"

class HarassmentManager
{
public:
	HarassmentManager();
	~HarassmentManager() = default;

	int getTargetPriority(BWAPI::Unit unit, BWAPI::Race enemyRace);

	static int LOWEST_PRIORITY;

private:

	typedef std::vector<std::function<bool(BWAPI::Unit)>> PriorityList;

	PriorityList m_EarlyTerranNoBunker{};
	PriorityList m_EarlyTerranWithBunker{};
	PriorityList m_EarlyProtoss{};
	PriorityList m_EarlyZerg{};

	PriorityList* m_currentPriorityList{};

	void computePriorityList(BWAPI::Race enemyRace);

	int evaluatePriority(BWAPI::Unit unit, std::vector<std::function<bool(BWAPI::Unit)>> &priorityList);
};