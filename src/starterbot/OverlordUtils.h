#pragma once

#include "BT.h"

class OverlordUtils
{
public:
	static BT_NODE* CreateIndividualTree(BWAPI::Unit overlord) {
		if (Tools::CountUnitsOfType(BWAPI::UnitTypes::Zerg_Overlord, BWAPI::Broodwar->self()->getUnits()) > 1) {
			// not the first overlord, so we will do something else
			return new BT_ACTION_IDLE("Idle", nullptr);
		}

		BT_DECO_CONDITION_UNIT_IDLE* isIdle = new BT_DECO_CONDITION_UNIT_IDLE("IsIdle", overlord, nullptr);
		BT_ACTION_GO_TO_ENEMY_BASE* goToEnemyBase = new BT_ACTION_GO_TO_ENEMY_BASE("GoToEnemyBase", overlord, isIdle);

		return isIdle;
	}

	static BT_NODE* CreateTrainingTree(BT_NODE* parent) {
		// if we have enough supply, train an overlord
		BT_DECO_CONDITION_NOT_ENOUGH_OVERLORDS* notEnoughOverlords = new BT_DECO_CONDITION_NOT_ENOUGH_OVERLORDS("NotEnoughOverlords", parent);
		// train overlord
		BT_ACTION_TRAIN_UNIT* trainOverlord = new BT_ACTION_TRAIN_UNIT("TrainOverlord", BWAPI::UnitTypes::Zerg_Overlord, false, notEnoughOverlords);

		return notEnoughOverlords;
	}
};