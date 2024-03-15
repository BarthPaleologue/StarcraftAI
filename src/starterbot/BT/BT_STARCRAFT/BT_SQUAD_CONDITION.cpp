#include "BT_SQUAD_CONDITION.h"

BT_SQUAD_CONDITION::BT_SQUAD_CONDITION(std::string name, Squad squad, BT_NODE* parent, CONDITION_CBK conditionCBK)
    :BT_NODE(name, parent, 0), m_squad(squad), ConditionCBK(conditionCBK) {

}

BT_NODE::State BT_SQUAD_CONDITION::Evaluate(void* data) {
    assert(ConditionCBK);
    if (ConditionCBK(m_squad, data)) return Success();
    else return Failure();
}

std::string BT_SQUAD_CONDITION::GetDescription()
{
    return "SQUAD_CONDITION";
}