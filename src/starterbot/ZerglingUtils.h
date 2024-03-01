#pragma once

#include "BT.h"

class ZerglingUtils
{
public:
	static BT_NODE* CreateTree(BWAPI::Unit zergling) {
		BT_DECO_CONDITION_BUILD_ORDER_FINISHED* buildOrderFinished = new BT_DECO_CONDITION_BUILD_ORDER_FINISHED("BuildOrderFinished", nullptr);
		auto goToEnemyBase = new BT_ACTION_GO_TO_ENEMY_BASE("MoveToEnemyBase", zergling, buildOrderFinished);

		return buildOrderFinished;
	}
};