#pragma once
#include "BT_ACTION.h"
#include "targeting/Squad.h"

class BT_ACTION_MUTALISK_SQUAD_FLEE_ANTI_AIR :
    public BT_ACTION
{
public:
	BT_ACTION_MUTALISK_SQUAD_FLEE_ANTI_AIR(std::string name, Squad squad, BT_NODE* parent);
private:
	BT_NODE::State Evaluate(void* data) override;
	std::string GetDescription() override;
	BT_NODE::State FleeAntiAir(void* data);

	Squad m_squad;
};

