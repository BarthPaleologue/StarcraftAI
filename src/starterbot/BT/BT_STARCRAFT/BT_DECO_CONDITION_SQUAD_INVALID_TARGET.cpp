#include "BT_DECO_CONDITION_SQUAD_INVALID_TARGET.h"

BT_DECO_CONDITION_SQUAD_INVALID_TARGET::BT_DECO_CONDITION_SQUAD_INVALID_TARGET(std::string name, Squad* squad, BT_NODE* parent)
	:BT_DECO_SQUAD_CONDITION(name, parent, squad, IsTargetInvalid)
{
}

std::string BT_DECO_CONDITION_SQUAD_INVALID_TARGET::GetDescription()
{
	return "BT_DECO_CONDITION_SQUAD_INVALID_TARGET";
}

bool BT_DECO_CONDITION_SQUAD_INVALID_TARGET::IsTargetInvalid(Squad* squad, void* data)
{
	BWAPI::Unit target = squad->getTarget();
	if (target == nullptr) return true; // if no target
	if (!target->exists()) return true; // if target is dead

	return false;
}
