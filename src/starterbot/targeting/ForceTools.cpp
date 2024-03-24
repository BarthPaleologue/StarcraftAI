
#include "ForceTools.h"
//implemented a fight predictor based on the following article :
// https://www.researchgate.net/publication/313904776_Combat_Outcome_Prediction_for_RTS_Games
//this article itself is based on the Lanchester Attrition's model. 

// In a nutshell : we model the fights using paired differential equations. These
// equations aren't linear in the general case, so we can't solve them explicitly. 
// Thus, the article generalizes the results obtained when these equations are linear ! 


float ForceTools::unitDPS(BWAPI::UnitType typeFrom, BWAPI::Player playerFrom, BWAPI::UnitType typeTo, BWAPI::Player playerTo) {
	try {

		BWAPI::Player enemy = BWAPI::Broodwar->enemy();
		BWAPI::Player me = BWAPI::Broodwar->self();

		int baseDamage = BWAPI::Broodwar->getDamageFrom(typeFrom, typeTo, me, enemy);
		if (baseDamage == 0) { return 0; }

		float damage = baseDamage * typeFrom.maxGroundHits();
		float cooldown = typeFrom.groundWeapon().damageCooldown();		;

		if(typeTo.isFlyer()){
			cooldown = typeFrom.airWeapon().damageCooldown();
			damage = baseDamage * typeFrom.maxAirHits();
		}
		
		float DPS = damage / cooldown;
		return DPS;
	} 
	catch(...){ 
		return 0.0; 
	}
}


float ForceTools::weaponRange(BWAPI::UnitType typeFrom, BWAPI::Player playerFrom, BWAPI::UnitType typeTo) {
	//range is in pixel;
	try {
		BWAPI::WeaponType wpn = typeFrom.groundWeapon();
		if (typeTo.isFlyer()) {
			wpn = typeFrom.airWeapon();
		}
		return playerFrom->weaponMaxRange(wpn);
	}
	catch (...) {
		return 0.0;
	}
}

float ForceTools::unitScore(int nFrom, BWAPI::UnitType typeFrom,BWAPI::Player PlayerFrom ,BWAPI::UnitType typeTo, BWAPI::Player PlayerTo,float n) {
	float firePowerRatio = unitDPS(typeFrom,PlayerFrom, typeTo,PlayerTo) / (typeTo.maxHitPoints());

	float hitPoints = nFrom;

	float score = firePowerRatio *pow( hitPoints,n);

	return score;
}

std::pair<float, float> ForceTools::engagedCombatPrediction(float nA, BWAPI::UnitType typeA, BWAPI::Player playerA,float nB, BWAPI::UnitType typeB, BWAPI::Player playerB,float n) {
	float scoreA = ForceTools::unitScore(nA,typeA,playerA, typeB,playerB);
	float scoreB = ForceTools::unitScore(nB,typeB,playerB, typeA,playerA);

	if (scoreA == 0 && scoreB==0 || scoreA==scoreB) {
		return std::pair<int, int>(nA, nB);
	}
	if (scoreA == 0) {
		return std::pair<int, int>(0, nB);
	}
	if (scoreB == 0) {
		return std::pair<int, int>(nA, 0);
	}
	float resultB=0, resultA=0;
	if (scoreA > scoreB) {
		resultA = nA * pow(1 - scoreB / scoreA, (1 / n));
	}
	else {
		resultB = nB * pow(1 - scoreA / scoreB, (1 / n));
	}

	return std::pair<float, float>(resultA, resultB);

}

float ForceTools::chargingPrediction(int nAtt, BWAPI::UnitType typeAtt, BWAPI::Player playerAtt, int nDef, BWAPI::UnitType typeDef, BWAPI::Player playerDef) {
	//time is expressed in frame.
	//length is expressed in pixel
	double speed = playerAtt->topSpeed(typeAtt);
	double DPS = ForceTools::unitDPS(typeDef, playerDef, typeAtt, playerAtt) * nDef / typeAtt.maxHitPoints();
	double size = typeAtt.tileSize().x*32;

	float denom = speed - DPS * size;
	if (denom <= 0) {
		//attackers are killed faster than they run.
		return 0.0;
	}
	
	double range = playerDef->weaponMaxRange(typeDef.groundWeapon());
	if (typeAtt.isFlyer()) {
		range= playerDef->weaponMaxRange(typeDef.airWeapon());
	}

	double killed = (range * DPS) / denom;
	double remaining = nAtt - killed;
	if (remaining < 0) { return 0; }
	return remaining;
}

std::pair<float, float> ForceTools::fightPredictor(int nA,BWAPI::UnitType typeA,BWAPI::Player playerA,int nB,BWAPI::UnitType typeB,BWAPI::Player playerB) {
	//As always, ranges are in pixel
	double rangeA = weaponRange(typeA, playerA, typeB);
	double rangeB = weaponRange(typeB, playerB, typeA);

	if (rangeA < 32 && rangeB<32) {
		//full melee combat : n = 1.
		return engagedCombatPrediction(nA, typeA, playerA, nB, typeB, playerB, 1);
	}
	else if (rangeA > 32 && rangeB > 32) {
		//full ranged combat : n = 1.
		return engagedCombatPrediction(nA, typeA, playerA, nB, typeB, playerB, 2);
	}
	else if (rangeA > 32 && rangeB < 32) {
		float newNB = chargingPrediction(nB, typeB, playerB, nA, typeA, playerA);
		return engagedCombatPrediction(nA, typeA, playerA, newNB, typeB, playerB, 1);
	}
	else if (rangeA < 32 && rangeB > 32) {
		float newNA = chargingPrediction(nA, typeA, playerA, nB, typeB, playerB);
		return engagedCombatPrediction(newNA, typeA, playerA, nB, typeB, playerB, 1);
	}
	else {
		throw "Error in fightPredictor";
	}
};

