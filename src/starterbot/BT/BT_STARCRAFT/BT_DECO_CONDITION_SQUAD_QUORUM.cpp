#include "BT_DECO_CONDITION_SQUAD_QUORUM.h"

BT_DECO_CONDITION_SQUAD_QUORUM::BT_DECO_CONDITION_SQUAD_QUORUM(std::string name, Squad* squad, BT_NODE* parent, int quorum, bool triggerOnlyOnce)
    : ConditionCBK(IsQuorumReached), BT_DECORATOR(name, parent), m_squad(squad), m_quorum(quorum), m_triggerOnlyOnce(triggerOnlyOnce)
{
}


BT_NODE::State BT_DECO_CONDITION_SQUAD_QUORUM::Evaluate(void* data) {
	assert(ConditionCBK);
	if (ConditionCBK(m_squad, m_quorum, m_triggerOnlyOnce, m_hasAlreadyTriggered, data)) {
		m_hasAlreadyTriggered = true;
		return ReturnState(BT_DECORATOR::Evaluate(data));
	}
	else return Failure();
}

std::string BT_DECO_CONDITION_SQUAD_QUORUM::GetDescription()
{
	return "BT_DECO_CONDITION_SQUAD_QUORUM";
}

bool BT_DECO_CONDITION_SQUAD_QUORUM::IsQuorumReached(Squad* squad, int quorum, bool triggerOnlyOnce, bool hasAlreadyTriggered, void* data)
{
	if (triggerOnlyOnce && hasAlreadyTriggered) return true;

	return squad->getNbUnits() >= quorum;
}
