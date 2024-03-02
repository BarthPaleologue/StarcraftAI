#include "BT_DECO_CONDITION_UNIT_IDLE.h"

BT_DECO_CONDITION_UNIT_IDLE::BT_DECO_CONDITION_UNIT_IDLE(std::string name, BWAPI::Unit unit, BT_NODE* parent)
	:BT_DECO_UNIT_CONDITION(name, parent, unit, IsIdle)
{

}

std::string BT_DECO_CONDITION_UNIT_IDLE::GetDescription()
{
	return "BT_DECO_CONDITION_UNIT_IDLE";
}

bool BT_DECO_CONDITION_UNIT_IDLE::IsIdle(BWAPI::Unit unit, void* data)
{
	if (unit->isSelected()) return false;
	else return unit->isIdle();
}

