#pragma once

#include "BWAPI.h"

namespace TargetingTools {
	//------------ constants ------------
	double const GAS_TO_MINERAL_FACTOR = 9. / 3.; // on each base, estimate 9 on minerals and 3 on gas (can count after scouting though)
	
	//------------ utility functions ----------------
	int unitCost(BWAPI::UnitType _unitType, double _gasFactor);
	double gasFactor(int _baseCount);
}