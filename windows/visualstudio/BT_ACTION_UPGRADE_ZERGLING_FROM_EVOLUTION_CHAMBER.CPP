#include "BT_ACTION_UPGRADE_ZERGLING_FROM_EVOLUTION_CHAMBER.h"
#include "BWAPI.h"
#include "Tools.h"

BT_ACTION_UPGRADE_ZERGLING_FROM_EVOLUTION_CHAMBER::BT_ACTION_UPGRADE_ZERGLING_FROM_EVOLUTION_CHAMBER(std::string name, BT_NODE* parent)
	:BT_ACTION(name, parent)
{
}

BT_NODE::State BT_ACTION_UPGRADE_ZERGLING_FROM_EVOLUTION_CHAMBER::Evaluate(void* data)
{
	return ReturnState(ChooseUpgrade(data));
}

std::string BT_ACTION_UPGRADE_ZERGLING_FROM_EVOLUTION_CHAMBER::GetDescription()
{
	return "BT_ACTION_UPGRADE_ZERGLING_FROM_EVOLUTION_CHAMBER";
}

BT_NODE::State BT_ACTION_UPGRADE_ZERGLING_FROM_EVOLUTION_CHAMBER::ChooseUpgrade(void* data)
{
	if(BWAPI::Broodwar->self()->isUpgrading(BWAPI::UpgradeTypes::Zerg_Melee_Attacks))
	{
		return BT_NODE::SUCCESS;
	}

	int currentMeleeUpgradeLevel = BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Zerg_Melee_Attacks);
	int maxMeleeUpgradeLevel = BWAPI::Broodwar->self()->getMaxUpgradeLevel(BWAPI::UpgradeTypes::Zerg_Melee_Attacks);

	if (currentMeleeUpgradeLevel < maxMeleeUpgradeLevel) {
		std::vector<BWAPI::Unit> evoChambers;
		Tools::GetAllUnitsOfType(BWAPI::UnitTypes::Zerg_Evolution_Chamber, evoChambers);
		for (auto evoChamber : evoChambers) {
			if (evoChamber->isCompleted() && evoChamber->isIdle()) {
				evoChamber->upgrade(BWAPI::UpgradeTypes::Zerg_Melee_Attacks);
				return BT_NODE::SUCCESS;
			}
		}
	}

	if(BWAPI::Broodwar->self()->isUpgrading(BWAPI::UpgradeTypes::Zerg_Carapace))
	{
		return BT_NODE::SUCCESS;
	}

	int currentCarapaceUpgradeLevel = BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Zerg_Carapace);
	int maxCarapaceUpgradeLevel = BWAPI::Broodwar->self()->getMaxUpgradeLevel(BWAPI::UpgradeTypes::Zerg_Carapace);

	if (currentCarapaceUpgradeLevel < maxCarapaceUpgradeLevel) {
		std::vector<BWAPI::Unit> evoChambers;
		Tools::GetAllUnitsOfType(BWAPI::UnitTypes::Zerg_Evolution_Chamber, evoChambers);
		for (auto evoChamber : evoChambers) {
			if (evoChamber->isCompleted() && evoChamber->isIdle()) {
				evoChamber->upgrade(BWAPI::UpgradeTypes::Zerg_Carapace);
				return BT_NODE::SUCCESS;
			}
		}
	}

	return BT_NODE::FAILURE;
}
