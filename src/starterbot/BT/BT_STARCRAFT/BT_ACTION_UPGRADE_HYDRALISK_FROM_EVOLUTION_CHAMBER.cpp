#include "BT_ACTION_UPGRADE_HYDRALISK_FROM_EVOLUTION_CHAMBER.h"
#include "BWAPI.h"
#include "Tools.h"

BT_NODE::State BT_ACTION_UPGRADE_HYDRALISK_FROM_EVOLUTION_CHAMBER::Evaluate(void* data)
{
    return ReturnState(ChooseUpgrade(data));
}

std::string BT_ACTION_UPGRADE_HYDRALISK_FROM_EVOLUTION_CHAMBER::GetDescription()
{
    return "BT_ACTION_UPGRADE_HYDRALISK_FROM_EVOLUTION_CHAMBER";
}

BT_NODE::State BT_ACTION_UPGRADE_HYDRALISK_FROM_EVOLUTION_CHAMBER::ChooseUpgrade(void* data)
{
    if (BWAPI::Broodwar->self()->isUpgrading(BWAPI::UpgradeTypes::Zerg_Missile_Attacks)) {
        return BT_NODE::State::SUCCESS;
    }

    int currentMissileLevel = BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Zerg_Missile_Attacks);
    int maxMissileLevel = BWAPI::Broodwar->self()->getMaxUpgradeLevel(BWAPI::UpgradeTypes::Zerg_Missile_Attacks);

    if (currentMissileLevel < maxMissileLevel) {
        std::vector<BWAPI::Unit> evolutionChambers;
        Tools::GetAllUnitsOfType(BWAPI::UnitTypes::Zerg_Evolution_Chamber, evolutionChambers);
        for (auto evolutionChamber : evolutionChambers) {
            if (evolutionChamber->isCompleted() && evolutionChamber->isIdle()) {
                if (evolutionChamber->upgrade(BWAPI::UpgradeTypes::Zerg_Missile_Attacks)) {
					return BT_NODE::State::RUNNING;
				}
			}
		}
	}

	if (BWAPI::Broodwar->self()->isUpgrading(BWAPI::UpgradeTypes::Zerg_Carapace)) {
		return BT_NODE::State::SUCCESS;
	}

	int currentCarapaceLevel = BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Zerg_Carapace);
	int maxCarapaceLevel = BWAPI::Broodwar->self()->getMaxUpgradeLevel(BWAPI::UpgradeTypes::Zerg_Carapace);

	if (currentCarapaceLevel < maxCarapaceLevel) {
		std::vector<BWAPI::Unit> evolutionChambers;
		Tools::GetAllUnitsOfType(BWAPI::UnitTypes::Zerg_Evolution_Chamber, evolutionChambers);
		for (auto evolutionChamber : evolutionChambers) {
			if (evolutionChamber->isCompleted() && evolutionChamber->isIdle()) {
				if (evolutionChamber->upgrade(BWAPI::UpgradeTypes::Zerg_Carapace)) {
					return BT_NODE::State::RUNNING;
				}
			}
		}
	}

	return BT_NODE::State::SUCCESS;
}


