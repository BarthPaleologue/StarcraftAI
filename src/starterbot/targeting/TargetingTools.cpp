#include "TargetingTools.h"

//using namespace TargetingTools;

/*
* USEFUL FOR SELF (FOR CODING)
* every info is in UnitType
* UnitType::mineralPrice() / gasPrice()
* Game::getDamageFrom / getDamageTo
* 
* depends on what we want to target, give different factors depending on what we want to target (see “harassing?
depending on cost : MINERAL_COST + GAS_COST * GAS_FACTOR(BASE_COUNT)

*/

/// <summary>
/// Returns a "unit cost" of minerals + gas (with a certain factor)
/// TODO: Can be a good indicator of power with _gasFactor = 1
/// </summary>
/// <returns></returns>
int TargetingTools::unitCost(BWAPI::UnitType _unitType, double _gasFactor) {
	return _unitType.mineralPrice() + _unitType.gasPrice() * _gasFactor;
}

double TargetingTools::gasFactor(int _baseCount) {
	return 1 + TargetingTools::GAS_TO_MINERAL_FACTOR / _baseCount;
}

/*
depending on how hard to kill :
	calculate / simulate damage
	enables finishing off targets
	use nearbyFriendlyUnitDamage = damage that can be dealt by the friendly units nearby (check “damage calculation?
	remainingHP / nearbyFriendlyUnitDamage
depending on how much damage it can deal potentially to us
	nerf for useless enemy units and for workers or buff for good counter units (notably splash damage)
	depending on how damaging it is for the enemy
essential abilities : 
	healing
	detecting cloak, anti-air: 1/x * (myUnitCountThatBenefits) (note: x also includes terran scanners, + numberOfEnemyBases if we see a scanner once)
buildings:
	is it the only unit production site / is it essential for production? (barracks, command center) -> 1/x
	for pylons: check 1/x for the buildings powered by it
	is it still useful (research buildings)
	does it block tech tree
	which kind of units it can produce (barracks)
how much I overextend
	enemy units around -> damage I may take for trying to target this
	allied units around -> is it still ok bc I have allies behind me so it’s ok if I die (or else major penalty)
	distance (low factor, mainly in nbOfEnemiesAround)
should be picking off edge units if they are all the same
*/

/// <summary>
/// zerg:
/// zergling
/// sunken colony
/// sunken colony that's being morphed
/// drone attacking zerglings
/// spawning pool(morphed or not)
/// drones
/// </summary>
/// <param name="unit"></param>
/// <returns></returns>
int TargetingTools::enemyZergPriorityScore(BWAPI::Unit unit)
{
	int score = 0;

	if(unit->getType() == BWAPI::UnitTypes::Zerg_Zergling) return score;
	score--;

	if (unit->getType() == BWAPI::UnitTypes::Zerg_Sunken_Colony) return score;
	score--;

	if (unit->getType() == BWAPI::UnitTypes::Zerg_Drone) {
		if (unit->isAttacking()) return score;
	}
	score--;

	if (unit->getType() == BWAPI::UnitTypes::Zerg_Spawning_Pool) return score;
	score--;

	if (unit->getType() == BWAPI::UnitTypes::Zerg_Drone) return score;

	return LOWEST_PRIORITY;
}

/// <summary>
/// terran if no bunker built:
/// scv building bunker
/// scv building barracks
/// scv attacking zerglings
/// marine attacking zergling
/// barracks(check if it's on the ground btw)
///	SCV
/// supply depot
/// other GROUND units(not possible to kill floating buildings)
///
///	terran if bunker built(not prio) :
/// marine(absolutely crucial)
/// SCV attacking zerglings
/// SCV repairing bunker
/// bunker
/// (afterwards returns to "no bunker")
/// </summary>
/// <param name="unit"></param>
/// <returns></returns>
int TargetingTools::enemyTerranPriorityScore(BWAPI::Unit unit)
{
	int score = 0;

	bool isBunkerBuilt = false;
	for (auto& unit : BWAPI::Broodwar->enemy()->getUnits()) {
		if (unit->getType() == BWAPI::UnitTypes::Terran_Bunker) {
			isBunkerBuilt = true;
			break;
		}
	}

	if (!isBunkerBuilt) {
		if (unit->getType() == BWAPI::UnitTypes::Terran_SCV) {
			if (unit->isConstructing() && unit->getBuildType() == BWAPI::UnitTypes::Terran_Bunker) return score;
		}
		score--;

		if (unit->getType() == BWAPI::UnitTypes::Terran_SCV) {
			if (unit->isConstructing() && unit->getBuildType() == BWAPI::UnitTypes::Terran_Barracks) return score;
		}
		score--;

		if (unit->getType() == BWAPI::UnitTypes::Terran_SCV) {
			if (unit->isAttacking()) return score;
		}
		score--;

		if (unit->getType() == BWAPI::UnitTypes::Terran_Marine) {
			if (unit->isAttacking()) return score;
		}
		score--;

		if (unit->getType() == BWAPI::UnitTypes::Terran_Barracks && unit->isCompleted()) {
			if (!unit->isLifted()) return score;
		}
		score--;

		if (unit->getType() == BWAPI::UnitTypes::Terran_SCV) return score;
		score--;

		if (unit->getType() == BWAPI::UnitTypes::Terran_Supply_Depot) return score;
		score--;

		if (!unit->getType().isBuilding()) return score;
		score--;
	}
	else {
		if (unit->getType() == BWAPI::UnitTypes::Terran_Marine) return score;
		score--;

		if (unit->getType() == BWAPI::UnitTypes::Terran_SCV) {
			if (unit->isAttacking()) return score;
		}
		score--;

		if (unit->getType() == BWAPI::UnitTypes::Terran_SCV) {
			if (unit->isRepairing()) return score;
		}
		score--;

		if (unit->getType() == BWAPI::UnitTypes::Terran_Bunker) return score;
		score--;
	}

	return LOWEST_PRIORITY;
}


/// <summary>
/// photon cannon that's built
/// photon cannon that's being built
/// probe attacking zerglings
/// zealot attacking zerglings
/// pylons
/// probes
/// </summary>
/// <param name="unit"></param>
/// <returns></returns>
int TargetingTools::enemyProtossPriorityScore(BWAPI::Unit unit)
{
	int score = 0;

	if (unit->getType() == BWAPI::UnitTypes::Protoss_Photon_Cannon) return score;
	score--;

	if (unit->getType() == BWAPI::UnitTypes::Protoss_Photon_Cannon) {
		if (unit->isBeingConstructed()) return score;
	}
	score--;

	if (unit->getType() == BWAPI::UnitTypes::Protoss_Probe) {
		if (unit->isAttacking()) return score;
	}
	score--;

	if (unit->getType() == BWAPI::UnitTypes::Protoss_Zealot) {
		if (unit->isAttacking()) return score;
	}
	score--;

	if (unit->getType() == BWAPI::UnitTypes::Protoss_Pylon) return score;
	score--;

	if (unit->getType() == BWAPI::UnitTypes::Protoss_Probe) return score;

	return LOWEST_PRIORITY;
}
