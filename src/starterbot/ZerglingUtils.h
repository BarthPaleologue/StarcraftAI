#pragma once

#include "BT.h"

class ZerglingUtils
{
public:
	static BT_NODE* CreateTree(BWAPI::Unit zergling) {
		BT_DECO_CONDITION_BUILD_ORDER_FINISHED* buildOrderFinished = new BT_DECO_CONDITION_BUILD_ORDER_FINISHED("BuildOrderFinished", nullptr);

		BT_SELECTOR* root = new BT_SELECTOR("Root", buildOrderFinished, 10);

		BT_DECO_CONDITION_UNIT_IS_IN_ENEMY_BASE* isInEnemyBase = new BT_DECO_CONDITION_UNIT_IS_IN_ENEMY_BASE("IsInEnemyBase", zergling, root);

		// choose which unit to attack
		BT_ACTION_SMART_ATTACK* smartAttack = new BT_ACTION_SMART_ATTACK("SmartAttack", zergling, root);

		// else, move to enemy base
		auto goToEnemyBase = new BT_ACTION_GO_TO_ENEMY_BASE("MoveToEnemyBase", zergling, root);

		return buildOrderFinished;
	}

	static BT_NODE* CreateTrainingTree(BT_NODE* parent) {
		BT_DECO_CONDITION_BUILD_ORDER_FINISHED* buildOrderFinished = new BT_DECO_CONDITION_BUILD_ORDER_FINISHED("BuildOrderFinished", parent);

		BT_ACTION_TRAIN_UNIT* trainZergling = new BT_ACTION_TRAIN_UNIT("TrainZergling", BWAPI::UnitTypes::Zerg_Zergling, true, buildOrderFinished);

		return buildOrderFinished;
	}
};