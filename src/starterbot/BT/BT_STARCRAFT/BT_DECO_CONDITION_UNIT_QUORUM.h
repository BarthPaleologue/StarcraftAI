#pragma once
#include "BT_DECORATOR.h"
#include <BWAPI.h>

class BT_DECO_CONDITION_UNIT_QUORUM :
    public BT_DECORATOR
{
public:
    typedef bool(*CONDITION_CBK)(BWAPI::UnitType unitType, int quorum, bool triggerOnlyOnce, bool m_hasAlreadyTriggered, void* data);
protected:
    CONDITION_CBK  ConditionCBK;
    BWAPI::UnitType    m_unitType;
    int m_quorum;
    bool m_hasAlreadyTriggered = false;
    bool m_triggerOnlyOnce;

public:
    BT_DECO_CONDITION_UNIT_QUORUM(std::string name, BWAPI::UnitType unitType, BT_NODE* parent, CONDITION_CBK conditionCBK, int quorum, bool triggerOnlyOnce);

    State Evaluate(void* data) override;

    std::string GetDescription() override;

    bool IsQuorumReached(BWAPI::UnitType unitType, int quorum, bool triggerOnlyOnce, bool hasAlreadyTriggered, void* data);
};

