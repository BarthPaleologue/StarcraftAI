#pragma once
#include "BT_ACTION.h"
#include "targeting/Squad.h"

class BT_ACTION_MUTALISK_SQUAD_ATTACK :
    public BT_ACTION
{
public:
	BT_ACTION_MUTALISK_SQUAD_ATTACK(std::string name, Squad* squad, BT_NODE* parent);
private:
	BT_NODE::State Evaluate(void* data) override;
	std::string GetDescription() override;
	BT_NODE::State Attack(void* data);

	Squad* m_squad;
};

