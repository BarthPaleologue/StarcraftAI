#pragma once
//implemented a fight predictor based on the following article :
// https://www.researchgate.net/publication/313904776_Combat_Outcome_Prediction_for_RTS_Games
//this article itself is based on the Lanchester Attrition's model. 

//In a nutshell : we model the fights using paired differential equations. These
// equations aren't linear in the general case, so we can't solve them explicitly. 
// Thus, the article generalizes the results obtained when these equations are linear ! 


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