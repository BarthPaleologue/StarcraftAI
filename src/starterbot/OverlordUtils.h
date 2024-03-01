#pragma once

#include "BT.h"

class OverlordUtils
{
public:
	static BT_NODE* CreateTree(BWAPI::Unit overlord) {
		BT_DECO_CONDITION_UNIT_IDLE* isIdle = new BT_DECO_CONDITION_UNIT_IDLE("IsIdle", overlord, nullptr);
		BT_ACTION_GO_TO_ENEMY_BASE* goToEnemyBase = new BT_ACTION_GO_TO_ENEMY_BASE("GoToEnemyBase", overlord, isIdle);

		return isIdle;
	}
};