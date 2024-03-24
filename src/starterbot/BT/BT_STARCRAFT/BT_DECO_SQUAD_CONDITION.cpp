#include "BT_DECO_SQUAD_CONDITION.h"

BT_DECO_SQUAD_CONDITION::BT_DECO_SQUAD_CONDITION(std::string name, BT_NODE* parent, Squad* squad, CONDITION_CBK conditionCBK)
	: BT_DECORATOR(name, parent), m_squad(squad), ConditionCBK(conditionCBK)
{
}


BT_NODE::State BT_DECO_SQUAD_CONDITION::Evaluate(void* data) {
    assert(ConditionCBK);
    if (ConditionCBK(m_squad, data))  return ReturnState(BT_DECORATOR::Evaluate(data));
    else return Failure();
}

std::string BT_DECO_SQUAD_CONDITION::GetDescription()
{
    return "DECO_SQUAD_CONDITION";
}