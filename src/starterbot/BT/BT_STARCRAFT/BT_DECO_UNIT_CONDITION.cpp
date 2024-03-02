#include "BT_DECO_UNIT_CONDITION.h"

BT_DECO_UNIT_CONDITION::BT_DECO_UNIT_CONDITION(std::string name, BT_NODE* parent, BWAPI::Unit unit, CONDITION_CBK conditionCBK)
	: ConditionCBK(conditionCBK), BT_DECORATOR(name, parent), m_unit(unit)
{

}

BT_NODE::State BT_DECO_UNIT_CONDITION::Evaluate(void* data) {
    assert(ConditionCBK);
    if (ConditionCBK(m_unit, data))  return ReturnState(BT_DECORATOR::Evaluate(data));
    else return Failure();
}

std::string BT_DECO_UNIT_CONDITION::GetDescription()
{
    return "DECO_UNIT_CONDITION";
}