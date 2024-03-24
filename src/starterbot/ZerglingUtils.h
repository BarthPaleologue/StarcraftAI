#pragma once

#include "BT.h"

class ZerglingUtils
{
public:
	static BT_NODE* CreateTree(BWAPI::Unit zergling) {
		auto root = new BT_DECO_REPEATER("repeater", nullptr, 0, true, false, true);

		auto chooseStrategy = new BT_SELECTOR("ChooseStrategy", root, 10);

		auto isAllIn = new BT_DECO_CONDITION_ALL_IN("isAllIn", chooseStrategy);

			auto allInStrategy = AllInStrategy(zergling, isAllIn);

		auto mainStrategy = MainStrategy(zergling, chooseStrategy);

		return root;
	}

	static BT_NODE* AllInStrategy(BWAPI::Unit zergling, BT_NODE* parent) {
		auto allInStrategy = new BT_SEQUENCER("AllInStrategy", parent, 10);

		auto allInGoToEnemyBase = new BT_ACTION_GO_TO_ENEMY_BASE("GoToEnemyBase", zergling, allInStrategy);

		auto allInSmartAttack = new BT_ACTION_SMART_ATTACK("SmartAttack", zergling, allInStrategy);

		return allInStrategy;
	}

	static BT_NODE* MainStrategy(BWAPI::Unit zergling, BT_NODE* parent) {
		auto mainStrategy = new BT_SEQUENCER("MainStrategy", parent, 10);

		auto quorumCondition = new BT_DECO_CONDITION_UNIT_QUORUM("zerglingQuorum", BWAPI::UnitTypes::Zerg_Zergling, mainStrategy, 4, true);

		auto goToEnemyBase = new BT_ACTION_GO_TO_ENEMY_BASE("GoToEnemyBase", zergling, quorumCondition);

		// choose which unit to attack
		auto smartAttack = new BT_ACTION_SMART_ATTACK("SmartAttack", zergling, mainStrategy);

		return mainStrategy;
	}

	static BT_NODE* TrainingTreeAllIn(BT_NODE* parent) {
		BT_DECO_CONDITION_BUILD_ORDER_FINISHED* buildOrderFinished = new BT_DECO_CONDITION_BUILD_ORDER_FINISHED("BuildOrderFinished", parent);

		BT_ACTION_TRAIN_UNIT* trainZergling = new BT_ACTION_TRAIN_UNIT("TrainZergling", BWAPI::UnitTypes::Zerg_Zergling, true, buildOrderFinished);

		return buildOrderFinished;
	}

	static BT_NODE* TrainingTreeEarly(BT_NODE* parent) {
		BT_DECO_CONDITION_BUILD_ORDER_FINISHED* root = new BT_DECO_CONDITION_BUILD_ORDER_FINISHED("BuildOrderFinished", parent);

		BT_DECO_CONDITION_NOT_ENOUGH_UNIT* unitCountCheck = new BT_DECO_CONDITION_NOT_ENOUGH_UNIT("NotEnoughZerglings", root, BWAPI::UnitTypes::Zerg_Zergling);

		BT_ACTION_TRAIN_UNIT* trainZergling = new BT_ACTION_TRAIN_UNIT("TrainZergling", BWAPI::UnitTypes::Zerg_Zergling, false, unitCountCheck);

		return root;
	}
};