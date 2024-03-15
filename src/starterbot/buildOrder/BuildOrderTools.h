#pragma once

#include <functional>
#include "BWAPI.h"
#include "Tools.h"

enum class e_buildOrderTimingType {
	Supply,
	Minerals, // necessary? just need to mash "build" and see when it starts
	HP
};

namespace BuildOrderTools {
	std::function<bool()> isTimingReached(e_buildOrderTimingType _type, int _timing);
	std::function<bool()> isSupplyTimingReached(int _supplyTiming);

	bool trainUnit(BWAPI::UnitType _unitType);

	BWAPI::Unit findStartedBuilding(BWAPI::UnitType _unitType);
	bool isBuildingStarted(BWAPI::UnitType _unitType);
	bool cancelConstruction(BWAPI::UnitType _unitType);
}