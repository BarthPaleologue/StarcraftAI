
#include "ForceTools.h"

float ForceTools::unitDPS(BWAPI::UnitType type, BWAPI::UnitType typeTo = BWAPI::UnitTypes::Zerg_Drone) {
	try {

		BWAPI::Player enemy = BWAPI::Broodwar->enemy();
		BWAPI::Player me = BWAPI::Broodwar->self();

		int damage = BWAPI::Broodwar->getDamageFrom(type, typeTo, me, enemy);
		
		if (damage == 0) { return 0; }
		damage = damage * type.maxGroundHits();
		
		int cooldown = type.groundWeapon().damageCooldown();
		;
		if(typeTo.isFlyer()){
			cooldown = type.airWeapon().damageCooldown();
		}
		
		float DPS = damage / float(cooldown);
		return DPS;
	} 
	catch(...){ 
		return 0.0; 
	}
}

float ForceTools::unitDPS(BWAPI::Unit unit, BWAPI::UnitType typeTo = BWAPI::UnitTypes::Zerg_Drone) {
	return ForceTools::unitDPS(unit->getType(),typeTo);
}

float ForceTools::unitScore(int nFrom, BWAPI::UnitType typeFrom, BWAPI::UnitType typeTo,float n=1.5) {
	float firePowerRatio = unitDPS(typeFrom, typeTo) / (typeTo.maxHitPoints());

	float hitPoints = nFrom;

	float score = firePowerRatio *pow( hitPoints,n);

	return score;
}

std::pair<float, float> ForceTools::combatPrediction(int nA, BWAPI::UnitType typeA, int nB, BWAPI::UnitType typeB,float n=1.5) {
	float scoreA = ForceTools::unitScore(nA,typeA, typeB);
	float scoreB = ForceTools::unitScore(nB,typeB, typeA);

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
void ForceTools::print_report(int nA, BWAPI::UnitType typeA, int nB, BWAPI::UnitType typeB,float n=1.5) {
	std::pair<float, float> pred = ForceTools::combatPrediction(nA, typeA, nB, typeB,n);
	std::cout << nA << " " << typeA.getName() << " against " << nB << " " << typeB.getName() << "  :  " << pred.first << " / " << pred.second << std::endl;

}
