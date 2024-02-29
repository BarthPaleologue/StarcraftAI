#pragma once

#include "BT.h"

class OverlordUtils
{
public:
	static BT_NODE* CreateTree(BWAPI::Unit overlord) {
		return new BT_ACTION_GO_TO_ENEMY_BASE("GoToEnnemyBase", overlord, nullptr);
	}
};