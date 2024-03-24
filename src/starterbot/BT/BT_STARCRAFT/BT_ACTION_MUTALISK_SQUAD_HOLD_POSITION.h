#pragma once
#include "BT_ACTION.h"
#include "targeting/Squad.h"

class BT_ACTION_MUTALISK_SQUAD_HOLD_POSITION :
    public BT_ACTION
{
public:
	BT_ACTION_MUTALISK_SQUAD_HOLD_POSITION(std::string name, Squad squad, BT_NODE* parent);
private:
	BT_NODE::State Evaluate(void* data) override;
	std::string GetDescription() override;
	BT_NODE::State HoldPosition(void* data);

	Squad m_squad;
};

