#include "ForceTools.h"

float ForceTools::unitForce(BWAPI::UnitType type) {
	try {
		BWAPI::UnitType drone = BWAPI::UnitTypes::Zerg_Drone;

		BWAPI::Player enemy = BWAPI::Broodwar->enemy();
		BWAPI::Player me = BWAPI::Broodwar->self();
		int damage = BWAPI::Broodwar->getDamageFrom(type, drone, me, enemy);
		
		if (damage == 0) { return 0; }
		damage = damage * type.maxGroundHits();
		int cooldown = type.groundWeapon().damageCooldown();
		float DPS = damage / float(cooldown);

		return DPS;
	} 
	catch(...){ 
		return 0.0; 
	}
}

float ForceTools::unitForce(BWAPI::Unit unit) {
	return ForceTools::unitForce(unit->getType());
}
