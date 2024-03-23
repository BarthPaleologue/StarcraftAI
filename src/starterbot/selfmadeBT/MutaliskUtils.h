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
		return new BT_ACTION_IDLE("MutaliskSquadIdle", parent);
	}
};