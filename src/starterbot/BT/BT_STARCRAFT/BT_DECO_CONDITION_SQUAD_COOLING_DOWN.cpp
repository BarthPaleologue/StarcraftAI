#include "BT_DECO_CONDITION_SQUAD_COOLING_DOWN.h"

BT_DECO_CONDITION_SQUAD_COOLING_DOWN::BT_DECO_CONDITION_SQUAD_COOLING_DOWN(std::string name, Squad* squad, BT_NODE* parent)
	: BT_DECO_SQUAD_CONDITION(name, parent, squad, IsCoolingDown)
{
}

std::string BT_DECO_CONDITION_SQUAD_COOLING_DOWN::GetDescription()
{
	return "BT_DECO_CONDITION_SQUAD_COOLING_DOWN";
}

bool BT_DECO_CONDITION_SQUAD_COOLING_DOWN::IsCoolingDown(Squad* squad, void* data)
{
	// check if all units in the squad are cooling down
	for (auto unit : squad->getUnits())
	{
		if (unit->getAirWeaponCooldown() > 0 || unit->getGroundWeaponCooldown() > 0 || unit->getSpellCooldown() > 0)
		{
			return false;
		}
	}

	return true;
}
