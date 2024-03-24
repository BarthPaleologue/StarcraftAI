#pragma once
#include "BT_ACTION.h"
#include "targeting/Squad.h"

class BT_ACTION_SQUAD_GO_TO_ENEMY_BASE :
    public BT_ACTION
{
public:
	BT_ACTION_SQUAD_GO_TO_ENEMY_BASE(std::string name, Squad* squad, BT_NODE* parent);
private:
	BT_NODE::State Evaluate(void* data) override;
	std::string GetDescription() override;
	BT_NODE::State GoToEnemyBase(void* data);

	Squad* m_squad;
};

