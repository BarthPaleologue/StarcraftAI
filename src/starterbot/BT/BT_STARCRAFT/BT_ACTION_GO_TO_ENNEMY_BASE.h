#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

class BT_ACTION_GO_TO_ENNEMY_BASE : public BT_ACTION
{
public:
	BT_ACTION_GO_TO_ENNEMY_BASE(std::string name, BWAPI::Unit unit, BT_NODE* parent);

private:
	State Evaluate(void* data) override;
	std::string GetDescription() override;
	BT_NODE::State GoToEnnemyBase(void* data);

	BWAPI::Unit m_unit;
};

