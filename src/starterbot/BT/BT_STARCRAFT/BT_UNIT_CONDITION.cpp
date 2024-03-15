#include "BT_UNIT_CONDITION.h"

BT_UNIT_CONDITION::BT_UNIT_CONDITION(std::string name, BWAPI::Unit unit, BT_NODE* parent, CONDITION_CBK conditionCBK)
	:BT_NODE(name, parent, 0), m_unit(unit), ConditionCBK(conditionCBK) {

}

BT_NODE::State BT_UNIT_CONDITION::Evaluate(void* data) {
    assert(ConditionCBK);
    if (ConditionCBK(m_unit, data)) return Success();
    else return Failure();
}

std::string BT_UNIT_CONDITION::GetDescription()
{
    return "UNIT_CONDITION";
}