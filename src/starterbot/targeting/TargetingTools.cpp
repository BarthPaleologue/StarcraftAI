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