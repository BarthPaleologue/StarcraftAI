#pragma once

#include "BT.h"

class ZerglingUtils
{
public:
	static BT_NODE* CreateTree(BWAPI::Unit zergling) {
		auto attackPlan = new BT_SEQUENCER("Root", nullptr, 10);

		// go to enemy base
		auto goToEnemyBase = new BT_ACTION_GO_TO_ENEMY_BASE("GoToEnemyBase", zergling, attackPlan);

		// choose which unit to attack
		auto smartAttack = new BT_ACTION_SMART_ATTACK("SmartAttack", zergling, attackPlan);

		return attackPlan;
	}

	static BT_NODE* CreateTrainingTree(BT_NODE* parent) {
		BT_DECO_CONDITION_BUILD_ORDER_FINISHED* buildOrderFinished = new BT_DECO_CONDITION_BUILD_ORDER_FINISHED("BuildOrderFinished", parent);

		BT_ACTION_TRAIN_UNIT* trainZergling = new BT_ACTION_TRAIN_UNIT("TrainZergling", BWAPI::UnitTypes::Zerg_Zergling, true, buildOrderFinished);

		return buildOrderFinished;
	}
};