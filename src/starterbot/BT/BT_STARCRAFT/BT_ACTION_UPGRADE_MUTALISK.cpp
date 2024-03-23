#include "BT_ACTION_UPGRADE_MUTALISK.h"
#include "BWAPI.h"
#include "Tools.h"

BT_ACTION_UPGRADE_MUTALISK::BT_ACTION_UPGRADE_MUTALISK(std::string name, BT_NODE* parent): BT_ACTION(name, parent)
{
}

BT_NODE::State BT_ACTION_UPGRADE_MUTALISK::Evaluate(void* data)
{
	return ReturnState(ChooseUpgrade(data));
}

std::string BT_ACTION_UPGRADE_MUTALISK::GetDescription()
{
	return "BT_ACTION_UPGRADE_MUTALISK";
}

BT_NODE::State BT_ACTION_UPGRADE_MUTALISK::ChooseUpgrade(void* data)
{
	if (BWAPI::Broodwar->self()->isUpgrading(BWAPI::UpgradeTypes::Zerg_Flyer_Carapace) || BWAPI::Broodwar->self()->isUpgrading(BWAPI::UpgradeTypes::Zerg_Flyer_Attacks))
	{
		return BT_NODE::RUNNING;
	}

	int carapaceLevel = BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Zerg_Flyer_Carapace);
	int attackLevel = BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Zerg_Flyer_Attacks);

	int carapaceMaxLevel = BWAPI::Broodwar->self()->getMaxUpgradeLevel(BWAPI::UpgradeTypes::Zerg_Flyer_Carapace);
	int attackMaxLevel = BWAPI::Broodwar->self()->getMaxUpgradeLevel(BWAPI::UpgradeTypes::Zerg_Flyer_Attacks);

	//TODO: only upgrade carapace if enemy has anti-air
	if (carapaceLevel < carapaceMaxLevel) {
		BWAPI::UnitType upgradeType = BWAPI::UpgradeTypes::Zerg_Flyer_Carapace.whatUpgrades();
		std::vector<BWAPI::Unit> units;
		Tools::GetAllUnitsOfType(upgradeType, units);
		for (auto unit : units)
		{
			if (unit->isIdle()) {
				unit->upgrade(BWAPI::UpgradeTypes::Zerg_Flyer_Carapace);
				return BT_NODE::SUCCESS;
			}
		}
	}

	if (attackLevel < attackMaxLevel) {
		BWAPI::UnitType upgradeType = BWAPI::UpgradeTypes::Zerg_Flyer_Attacks.whatUpgrades();
		std::vector<BWAPI::Unit> units;
		Tools::GetAllUnitsOfType(upgradeType, units);
		for (auto unit : units)
		{
			if (unit->isIdle()) {
				unit->upgrade(BWAPI::UpgradeTypes::Zerg_Flyer_Attacks);
				return BT_NODE::SUCCESS;
			}
		}
	}

	return BT_NODE::FAILURE;
}


