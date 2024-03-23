#include "BT_ACTION_UPGRADE_ZERGLING_FROM_SPAWNING_POOL.h"
#include "BWAPI.h"
#include "Tools.h"

BT_ACTION_UPGRADE_ZERGLING_FROM_SPAWNING_POOL::BT_ACTION_UPGRADE_ZERGLING_FROM_SPAWNING_POOL(std::string name, BT_NODE* parent)
	: BT_ACTION(name, parent)
{
}

BT_NODE::State BT_ACTION_UPGRADE_ZERGLING_FROM_SPAWNING_POOL::Evaluate(void* data)
{
	return ReturnState(ChooseUpgrade(data));
}

std::string BT_ACTION_UPGRADE_ZERGLING_FROM_SPAWNING_POOL::GetDescription()
{
	return "BT_ACTION_UPGRADE_ZERGLING_FROM_SPAWNING_POOL";
}

BT_NODE::State BT_ACTION_UPGRADE_ZERGLING_FROM_SPAWNING_POOL::ChooseUpgrade(void* data)
{
	if (BWAPI::Broodwar->self()->isUpgrading(BWAPI::UpgradeTypes::Adrenal_Glands)) {
		return BT_NODE::State::SUCCESS;
	}
	int currentAdrenalGlandsLevel = BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Adrenal_Glands);
	int maxAdrenalGlandsLevel = BWAPI::Broodwar->self()->getMaxUpgradeLevel(BWAPI::UpgradeTypes::Adrenal_Glands);

	if (currentAdrenalGlandsLevel < maxAdrenalGlandsLevel) {
		std::vector<BWAPI::Unit> spawningPools;
		Tools::GetAllUnitsOfType(BWAPI::UnitTypes::Zerg_Spawning_Pool, spawningPools);
		for(auto& spawningPool : spawningPools) {
			if (spawningPool->isCompleted() && spawningPool->isIdle()) {
				if (spawningPool->upgrade(BWAPI::UpgradeTypes::Adrenal_Glands)) {
					return BT_NODE::State::SUCCESS;
				}
			}
		}
	}

	if (BWAPI::Broodwar->self()->isUpgrading(BWAPI::UpgradeTypes::Metabolic_Boost)) {
		return BT_NODE::State::SUCCESS;
	}
	int currentMetabolicBoostLevel = BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Metabolic_Boost);
	int maxMetabolicBoostLevel = BWAPI::Broodwar->self()->getMaxUpgradeLevel(BWAPI::UpgradeTypes::Metabolic_Boost);

	if (currentMetabolicBoostLevel < maxMetabolicBoostLevel) {
		std::vector<BWAPI::Unit> spawningPools;
		Tools::GetAllUnitsOfType(BWAPI::UnitTypes::Zerg_Spawning_Pool, spawningPools);
		for (auto& spawningPool : spawningPools) {
			if (spawningPool->isCompleted() && spawningPool->isIdle()) {
				if (spawningPool->upgrade(BWAPI::UpgradeTypes::Metabolic_Boost)) {
					return BT_NODE::State::SUCCESS;
				}
			}
		}
	}

	return BT_NODE::State::FAILURE;
}
