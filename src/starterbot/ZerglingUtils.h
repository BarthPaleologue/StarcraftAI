#pragma once

#include "BT.h"

class ZerglingUtils
{
public:
	static BT_NODE* CreateTree(BWAPI::Unit zergling) {
		auto root = new BT_DECO_REPEATER("repeater", nullptr, 0, true, false, true);

		auto attackPlan = new BT_SEQUENCER("Root", root, 10);

		auto quorumCondition = new BT_DECO_CONDITION_UNIT_QUORUM("zerglingQuorum", BWAPI::UnitTypes::Zerg_Zergling, attackPlan, 4, true);

		// go to enemy base
		auto goToEnemyBase = new BT_ACTION_GO_TO_ENEMY_BASE("GoToEnemyBase", zergling, quorumCondition);

		// choose which unit to attack
		auto smartAttack = new BT_ACTION_SMART_ATTACK("SmartAttack", zergling, attackPlan);

		return root;
	}

	static BT_NODE* CreateTrainingTree(BT_NODE* parent) {
		BT_DECO_CONDITION_BUILD_ORDER_FINISHED* buildOrderFinished = new BT_DECO_CONDITION_BUILD_ORDER_FINISHED("BuildOrderFinished", parent);

		BT_ACTION_TRAIN_UNIT* trainZergling = new BT_ACTION_TRAIN_UNIT("TrainZergling", BWAPI::UnitTypes::Zerg_Zergling, true, buildOrderFinished);

		return buildOrderFinished;
	}
};