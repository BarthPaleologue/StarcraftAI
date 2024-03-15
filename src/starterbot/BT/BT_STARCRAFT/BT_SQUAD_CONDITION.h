#pragma once
#include "BT_NODE.h"
#include "targeting/Squad.h"

class BT_SQUAD_CONDITION :
    public BT_NODE
{
public:
	typedef bool(*CONDITION_CBK)(Squad squad, void* data);
protected:
	CONDITION_CBK  ConditionCBK;
	Squad    m_squad;

public:
	BT_SQUAD_CONDITION(std::string name, Squad squad, BT_NODE* parent, CONDITION_CBK conditionCBK);
	State Evaluate(void* data) override;
	std::string GetDescription() override;
};

