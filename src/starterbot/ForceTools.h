#pragma once

#include "BWAPI.h"

namespace ForceTools {

	float unitDPS(BWAPI::Unit unit, BWAPI::UnitType typeTo);
	float unitDPS(BWAPI::UnitType typeFrom, BWAPI::UnitType typeTo);

	float unitScore(int nFrom, BWAPI::UnitType typeFrom, BWAPI::UnitType typeTo,float n);
	
	std::pair<float,float> combatPrediction(int nA, BWAPI::UnitType typeA, int nB, BWAPI::UnitType typeB,float n);
	void print_report(int nA, BWAPI::UnitType typeA, int nB, BWAPI::UnitType typeB,float n);

}