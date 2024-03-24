#pragma once

#include "BT.h"

class MutaliskUtils
{
public:
	static BT_NODE* TrainingTree(BT_NODE* parent) {
		BT_DECO_CONDITION_BUILD_ORDER_FINISHED* root = new BT_DECO_CONDITION_BUILD_ORDER_FINISHED("BuildOrderFinished", parent);

		BT_DECO_CONDITION_NOT_ENOUGH_UNIT* unitCountCheck = new BT_DECO_CONDITION_NOT_ENOUGH_UNIT("NotEnoughMutalisks", root, BWAPI::UnitTypes::Zerg_Mutalisk);

		BT_ACTION_TRAIN_UNIT* trainMutalisks = new BT_ACTION_TRAIN_UNIT("TrainMutalisk", BWAPI::UnitTypes::Zerg_Mutalisk, true, unitCountCheck);

		return root;
	}

	static BT_NODE* SquadTree(Squad* squad, BT_NODE* parent) {
		auto root = new BT_DECO_REPEATER("repeater", nullptr, 0, true, false, true);

		auto chooseStrategy = new BT_SELECTOR("ChooseStrategy", root, 10);

			auto isAllIn = new BT_DECO_CONDITION_ALL_IN("IsAllIn", chooseStrategy);

			auto allInStrategy = AllInStrategy(squad, isAllIn);
			
			auto mainStrategy = MainStrategy(squad, chooseStrategy);
			
		return root;
	}

	static BT_NODE* AllInStrategy(Squad* squad, BT_NODE* parent) {
		auto allInStrategy = new BT_SEQUENCER("AllInStrategy", parent, 10);

		auto allInIsTargetInvalid = new BT_DECO_CONDITION_SQUAD_INVALID_TARGET("allInIsTargetInvalid", squad, allInStrategy);

		auto allInChooseTarget = new BT_ACTION_MUTALISK_SQUAD_CHOOSE_TARGET("allInChooseTarget", squad, allInIsTargetInvalid);

		auto allInAttack = new BT_ACTION_MUTALISK_SQUAD_ATTACK("AllInAttack", squad, allInStrategy);

		return allInStrategy;
	}

	static BT_NODE* MainStrategy(Squad* squad, BT_NODE* parent) {
		auto mainStrategy = new BT_PARALLEL_SEQUENCER("MainStrategy", parent, 10);

		auto isTargetInvalid = new BT_DECO_CONDITION_SQUAD_INVALID_TARGET("IsTargetInvalid", squad, mainStrategy);

		auto chooseTarget = new BT_ACTION_MUTALISK_SQUAD_CHOOSE_TARGET("ChooseTarget", squad, isTargetInvalid);

		auto attackActionSelector = new BT_SELECTOR("AttackActionSelector", mainStrategy, 10);

		auto isCoolingDown = new BT_DECO_CONDITION_SQUAD_COOLING_DOWN("IsCoolingDown", squad, attackActionSelector);

		auto fleeAction = new BT_ACTION_MUTALISK_SQUAD_HOLD_POSITION("Flee", squad, isCoolingDown);

		auto attackAction = new BT_ACTION_MUTALISK_SQUAD_ATTACK("Attack", squad, attackActionSelector);

		return mainStrategy;
	}
};