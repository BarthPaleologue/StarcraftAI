#pragma once

#include <BWAPI.h>
#include <set>

enum class BaseOwner
{
	UNKNOWN,
	FREE,
	ALLY,
	ENEMY,
};

class BaseManager {
public:
	int lastVisitedFrame = 0;
	BaseOwner owner = BaseOwner::UNKNOWN;// who has the command center
	std::set<BWAPI::Unit> enemyUnitsNearby; //includes buildings (enables cannon rush detection)
	std::set<BWAPI::Unit> allyDefensesNearby; //only sunkens / spores
};