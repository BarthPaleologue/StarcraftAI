#include "BT_ACTION_UPGRADE_HYDRALISK_FROM_DEN.h"
#include "Blackboard.h"
#include "BWAPI.h"
#include "Tools.h"

BT_NODE::State BT_ACTION_UPGRADE_HYDRALISK_FROM_DEN::Evaluate(void* data)
{
    return ReturnState(ChooseUpgrade(data));
}

std::string BT_ACTION_UPGRADE_HYDRALISK_FROM_DEN::GetDescription()
{
    return "BT_ACTION_UPGRADE_HYDRALISK_FROM_DEN";
}

BT_NODE::State BT_ACTION_UPGRADE_HYDRALISK_FROM_DEN::ChooseUpgrade(void* data)
{
    Blackboard* blackboard = ((Blackboard*)data);
    /* TODO: if (blackboard->needsLurker) { research lurker aspect } */

    if(BWAPI::Broodwar->self()->isUpgrading(BWAPI::UpgradeTypes::Muscular_Augments))
	{
		return BT_NODE::SUCCESS;
	}

    int currentMuscularAugmentsLevel = BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Muscular_Augments);
    int maxMuscularAugmentsLevel = BWAPI::Broodwar->self()->getMaxUpgradeLevel(BWAPI::UpgradeTypes::Muscular_Augments);

    if (currentMuscularAugmentsLevel < maxMuscularAugmentsLevel) {
        std::vector<BWAPI::Unit> dens;
        Tools::GetAllUnitsOfType(BWAPI::UnitTypes::Zerg_Hydralisk_Den, dens);

        for (auto den : dens) {
            if(den->isCompleted() && den->isIdle()) {
				den->upgrade(BWAPI::UpgradeTypes::Muscular_Augments);
				return BT_NODE::SUCCESS;
			}
        }
	}

	if (BWAPI::Broodwar->self()->isUpgrading(BWAPI::UpgradeTypes::Grooved_Spines)) {
		return BT_NODE::SUCCESS;
	}

	int currentGroovedSpinesLevel = BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Grooved_Spines);
	int maxGroovedSpinesLevel = BWAPI::Broodwar->self()->getMaxUpgradeLevel(BWAPI::UpgradeTypes::Grooved_Spines);

	if (currentGroovedSpinesLevel < maxGroovedSpinesLevel) {
		std::vector<BWAPI::Unit> dens;
		Tools::GetAllUnitsOfType(BWAPI::UnitTypes::Zerg_Hydralisk_Den, dens);

		for (auto den : dens) {
			if (den->isCompleted() && den->isIdle()) {
				den->upgrade(BWAPI::UpgradeTypes::Grooved_Spines);
				return BT_NODE::SUCCESS;
			}
		}
	}

	return BT_NODE::FAILURE;
}
