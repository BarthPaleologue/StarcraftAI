#pragma once

#include "BWAPI.h"

namespace ForceTools {
	float unitDPS(	BWAPI::UnitType typeFrom, 
					BWAPI::Player playerFrom=BWAPI::Broodwar->enemy(),
					BWAPI::UnitType typeTo=BWAPI::UnitTypes::Zerg_Drone, 
					BWAPI::Player playerTo=BWAPI::Broodwar->self()
	);

	float unitScore(	int nFrom, 
						BWAPI::UnitType typeFrom, 
						BWAPI::Player PlayerFrom, 
						BWAPI::UnitType typeTo, 
						BWAPI::Player PlayerTo, 
						float n = 1.5
	);
	
	float chargingPrediction(	int nAtt, 
								BWAPI::UnitType typeAtt, 
								BWAPI::Player playerAtt,
								int nDef, 
								BWAPI::UnitType typeDef, 
								BWAPI::Player playerDef);

	std::pair<float,float> engagedCombatPrediction(	float nA, 
												BWAPI::UnitType typeA, 
												BWAPI::Player playerA, 
												float nB, 
												BWAPI::UnitType typeB, 
												BWAPI::Player playerB, 
												float n=1.5);

	std::pair<float, float> fightPredictor(int nA,
		BWAPI::UnitType typeA,
		BWAPI::Player playerA,
		int nB,
		BWAPI::UnitType typeB,
		BWAPI::Player playerB
		);

	float weaponRange(	BWAPI::UnitType typeFrom, 
						BWAPI::Player playerFrom, 
						BWAPI::UnitType typeTo);
}