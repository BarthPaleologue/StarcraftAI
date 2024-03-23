#pragma once

#include "BT.h"

namespace BT_Builder {
	BT_NODE* buildUpgradeBT(BT_NODE* parent) {
		auto root = new BT_PARALLEL_SEQUENCER("UpgradeRoot", parent, 10);

		// Zergling Upgrades
		auto zerglingQuorum = new BT_DECO_CONDITION_UNIT_QUORUM("ZerglingQuorum", BWAPI::UnitTypes::Zerg_Zergling, root, 12, false);

		auto zerglingUpgradeSequencer = new BT_SEQUENCER("ZerglingUpgradeSequencer", zerglingQuorum, 2);

		auto zerglingUpgradeFromSpawningPool = new BT_ACTION_UPGRADE_ZERGLING_FROM_SPAWNING_POOL("UpgradeZerglingFromSpawningPool", zerglingUpgradeSequencer);

		auto zerglingUpgradeFromEvolutionChamber = new BT_ACTION_UPGRADE_ZERGLING_FROM_EVOLUTION_CHAMBER("UpgradeZerglingFromEvolutionChamber", zerglingUpgradeSequencer);

		// Hydralisk Upgrades
		auto hydraliskQuorum = new BT_DECO_CONDITION_UNIT_QUORUM("HydrasQuorum", BWAPI::UnitTypes::Zerg_Hydralisk, root, 6, false);

		auto hydraliskUpdateSequencer = new BT_SEQUENCER("HydrasUpdateSequencer", hydraliskQuorum, 2);

		auto hydraliskUpgradeFromHydraliskDen = new BT_ACTION_UPGRADE_HYDRALISK_FROM_DEN("UpgradeHydraliskFromHydraliskDen", hydraliskUpdateSequencer);

		// Ultralisk Upgrades
		auto ultraliskCavernQuorum = new BT_DECO_CONDITION_UNIT_QUORUM("UltraliskCavernQuorum", BWAPI::UnitTypes::Zerg_Ultralisk_Cavern, root, 1, false);

		auto upgradeUltralisk = new BT_ACTION_UPGRADE_ULTRALISK("UpgradeUltralisk", ultraliskCavernQuorum);

		// Defiler Upgrades
		auto defilerMoundQuorum = new BT_DECO_CONDITION_UNIT_QUORUM("DefilerMoundQuorum", BWAPI::UnitTypes::Zerg_Defiler_Mound, root, 1, false);

		auto upgradeDefiler = new BT_ACTION_UPGRADE_DEFILER("UpgradeDefiler", defilerMoundQuorum);

		// Mutalisk Upgrades
		auto mutaliskQuorum = new BT_DECO_CONDITION_UNIT_QUORUM("MutaliskQuorum", BWAPI::UnitTypes::Zerg_Mutalisk, root, 6, false);

		auto upgradeMutalisk = new BT_ACTION_UPGRADE_MUTALISK("UpgradeMutalisk", mutaliskQuorum);

		return root;
	}
}