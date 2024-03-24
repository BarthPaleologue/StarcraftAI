#pragma once
#include "BT_DECORATOR.h"
#include "targeting/Squad.h"

class BT_DECO_SQUAD_CONDITION :
    public BT_DECORATOR
{
public:
    typedef bool(*CONDITION_CBK)(Squad squad, void* data);
protected:
    CONDITION_CBK  ConditionCBK;
    Squad    m_squad;

public:
    BT_DECO_SQUAD_CONDITION(std::string name, BT_NODE* parent, Squad squad, CONDITION_CBK conditionCBK);
    State Evaluate(void* data) override;
    std::string GetDescription() override;
};

