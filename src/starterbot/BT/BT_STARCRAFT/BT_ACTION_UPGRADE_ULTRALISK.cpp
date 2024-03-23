#include "BT_ACTION_UPGRADE_ULTRALISK.h"
#include <BWAPI.h>
#include "Tools.h"

BT_ACTION_UPGRADE_ULTRALISK::BT_ACTION_UPGRADE_ULTRALISK(std::string name, BT_NODE* parent) : BT_ACTION(name, parent) {

}

BT_NODE::State BT_ACTION_UPGRADE_ULTRALISK::Evaluate(void* data)
{
	return ReturnState(ChooseUpgrade(data));
}

std::string BT_ACTION_UPGRADE_ULTRALISK::GetDescription()
{
	"BT_ACTION_UPGRADE_ULTRALISK";
}

BT_NODE::State BT_ACTION_UPGRADE_ULTRALISK::ChooseUpgrade(void* data)
{
	if (BWAPI::Broodwar->self()->isUpgrading(BWAPI::UpgradeTypes::Chitinous_Plating) || BWAPI::Broodwar->self()->isUpgrading(BWAPI::UpgradeTypes::Anabolic_Synthesis))
	{
		return BT_NODE::RUNNING;
	}

	int chitinousPlatingLevel = BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Chitinous_Plating);
	int anabolicSynthesisLevel = BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Anabolic_Synthesis);

	int chitinousPlatingMaxLevel = BWAPI::Broodwar->self()->getMaxUpgradeLevel(BWAPI::UpgradeTypes::Chitinous_Plating);
	int anabolicSynthesisMaxLevel = BWAPI::Broodwar->self()->getMaxUpgradeLevel(BWAPI::UpgradeTypes::Anabolic_Synthesis);

	if (chitinousPlatingLevel < chitinousPlatingMaxLevel) {
		BWAPI::UnitType upgradeType = BWAPI::UpgradeTypes::Chitinous_Plating.whatUpgrades();
		std::vector<BWAPI::Unit> units;
		Tools::GetAllUnitsOfType(upgradeType, units);
		for (auto unit : units)
		{
			if (unit->isIdle()) {
				unit->upgrade(BWAPI::UpgradeTypes::Chitinous_Plating);
				return BT_NODE::SUCCESS;
			}
		}
	}

	if (anabolicSynthesisLevel < anabolicSynthesisMaxLevel) {
		BWAPI::UnitType upgradeType = BWAPI::UpgradeTypes::Anabolic_Synthesis.whatUpgrades();
		std::vector<BWAPI::Unit> units;
		Tools::GetAllUnitsOfType(upgradeType, units);
		for (auto unit : units)
		{
			if (unit->isIdle()) {
				unit->upgrade(BWAPI::UpgradeTypes::Anabolic_Synthesis);
				return BT_NODE::SUCCESS;
			}
		}
	}

	return BT_NODE::FAILURE;
}


