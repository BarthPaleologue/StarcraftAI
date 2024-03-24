#include "BT_ACTION_MUTALISK_SQUAD_FLEE_ANTI_AIR.h"

BT_ACTION_MUTALISK_SQUAD_FLEE_ANTI_AIR::BT_ACTION_MUTALISK_SQUAD_FLEE_ANTI_AIR(std::string name, Squad squad, BT_NODE* parent)
	: BT_ACTION(name, parent), m_squad(squad)
{
}

BT_NODE::State BT_ACTION_MUTALISK_SQUAD_FLEE_ANTI_AIR::Evaluate(void* data)
{
	return ReturnState(FleeAntiAir(data));
}

std::string BT_ACTION_MUTALISK_SQUAD_FLEE_ANTI_AIR::GetDescription()
{
	return "BT_ACTION_MUTALISK_SQUAD_FLEE_ANTI_AIR";
}

BT_NODE::State BT_ACTION_MUTALISK_SQUAD_FLEE_ANTI_AIR::FleeAntiAir(void* data)
{
	// all enemy units nearby
	BWAPI::Unitset nearbyEnemies = m_squad.getEnemyUnitsInRadius(100.0f);

	// filter to only get anti-air units
	BWAPI::Unitset antiAirEnemies;
	for (auto& enemy : nearbyEnemies)
	{
		if (enemy->getType().airWeapon() != BWAPI::WeaponTypes::None)
		{
			antiAirEnemies.insert(enemy);
		}
	}

	// if there are no anti-air units nearby, return success
	if (antiAirEnemies.empty())
	{
		return BT_NODE::State::SUCCESS;
	}

	// otherwise, make a weighted flee vector (weighted by the inverse of the distance)
	BWAPI::Position fleeVector(0, 0);
	double weightSum = 0.0;
	for (auto& enemy : antiAirEnemies)
	{
		double distance = m_squad.getPosition().getDistance(enemy->getPosition());
		double weight = 1.0 / distance;
		BWAPI::Position weightedFleeVector = (m_squad.getPosition() - enemy->getPosition()) * weight * weight;
		fleeVector += weightedFleeVector;
		weightSum += weight;
	}

	// normalize the flee vector
	fleeVector = fleeVector / weightSum;

	// move the squad
	m_squad.moveTo(m_squad.getPosition() + fleeVector * 10);

	return BT_NODE::State::SUCCESS;
}
