#include "BT_DECO_CONDITION_UNIT_QUORUM.h"

BT_DECO_CONDITION_UNIT_QUORUM::BT_DECO_CONDITION_UNIT_QUORUM(std::string name, BWAPI::UnitType unitType, BT_NODE* parent, int quorum, bool triggerOnlyOnce)
    : ConditionCBK(IsQuorumReached), BT_DECORATOR(name, parent), m_unitType(unitType), m_quorum(quorum), m_triggerOnlyOnce(triggerOnlyOnce)
{
}

BT_NODE::State BT_DECO_CONDITION_UNIT_QUORUM::Evaluate(void* data) {
    assert(ConditionCBK);
	if (ConditionCBK(m_unitType, m_quorum, m_triggerOnlyOnce, m_hasAlreadyTriggered, data)) {
		m_hasAlreadyTriggered = true;
		return ReturnState(BT_DECORATOR::Evaluate(data));
	}
    else return Failure();
}

std::string BT_DECO_CONDITION_UNIT_QUORUM::GetDescription()
{
    return "BT_DECO_CONDITION_UNIT_QUORUM";
}

bool BT_DECO_CONDITION_UNIT_QUORUM::IsQuorumReached(BWAPI::UnitType unitType, int quorum, bool triggerOnlyOnce, bool hasAlreadyTriggered, void* data)
{
	if(triggerOnlyOnce && hasAlreadyTriggered) return true;

	int count = 0;
	for (auto& unit : BWAPI::Broodwar->self()->getUnits()) {
		if (unit->getType() != unitType) continue;
		if (!unit->isCompleted()) continue;
			
		count++;
	}
	return count >= quorum;
}
