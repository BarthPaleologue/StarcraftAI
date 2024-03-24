#pragma once
#include "BT_DECORATOR.h"
#include "targeting/Squad.h"

class BT_DECO_CONDITION_SQUAD_QUORUM :
    public BT_DECORATOR
{
public:
    typedef bool(*CONDITION_CBK)(Squad* squad, int quorum, bool triggerOnlyOnce, bool m_hasAlreadyTriggered, void* data);
protected:
    CONDITION_CBK  ConditionCBK;
    Squad*    m_squad;
    int m_quorum;
    bool m_hasAlreadyTriggered = false;
    bool m_triggerOnlyOnce;

public:
    BT_DECO_CONDITION_SQUAD_QUORUM(std::string name, Squad* squad, BT_NODE* parent, int quorum, bool triggerOnlyOnce);

    State Evaluate(void* data) override;

    std::string GetDescription() override;

    static bool IsQuorumReached(Squad* squad, int quorum, bool triggerOnlyOnce, bool hasAlreadyTriggered, void* data);
};

