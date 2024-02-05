#pragma once

#include <functional>
#include "BWAPI.h"
#include "Tools.h"

enum e_buildOrderTimingType {
	buildOrderTiming_SUPPLY,
	buildOrderTiming_MINERALS, // necessary? just need to mash "build" and see when it starts
	buildOrderTiming_HP
};

std::function<bool()> isSupplyTimingReached(int supplyTiming);