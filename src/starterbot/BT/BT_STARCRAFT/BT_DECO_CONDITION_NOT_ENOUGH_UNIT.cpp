#include "BT_DECO_CONDITION_NOT_ENOUGH_UNIT.h"
#include "Blackboard.h"

BT_DECO_CONDITION_NOT_ENOUGH_UNIT::BT_DECO_CONDITION_NOT_ENOUGH_UNIT(std::string name, BT_NODE* parent, BWAPI::UnitType unitType, int minAmount)
	: BT_DECO_CONDITION(name, parent, 0), m_unitTypeConcerned(unitType), m_minAmount(minAmount) {}

std::string BT_DECO_CONDITION_NOT_ENOUGH_UNIT::GetDescription()
{
	return "BT_DECO_NOT_ENOUGH " + m_unitTypeConcerned;
}

BT_NODE::State BT_DECO_CONDITION_NOT_ENOUGH_UNIT::Evaluate(void* data)
{
	Blackboard* pData = (Blackboard*)data;

	const int unitCount = Tools::CountUnitsOfType(m_unitTypeConcerned, BWAPI::Broodwar->self()->getUnits());
	if (unitCount < m_minAmount) {
		return ReturnState(BT_DECORATOR::Evaluate(data));
	}
	else return Failure();
}
