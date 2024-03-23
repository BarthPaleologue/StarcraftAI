#include "BT_ACTION_UPGRADE_DEFILER.h"
#include "Tools.h"
#include "BWAPI.h"

BT_ACTION_UPGRADE_DEFILER::BT_ACTION_UPGRADE_DEFILER(std::string name, BT_NODE* parent): BT_ACTION(name, parent)
{
}

BT_NODE::State BT_ACTION_UPGRADE_DEFILER::Evaluate(void* data)
{
	return ReturnState(ChooseUpgrade(data));
}

std::string BT_ACTION_UPGRADE_DEFILER::GetDescription()
{
	return "BT_ACTION_UPGRADE_DEFILER";
}

BT_NODE::State BT_ACTION_UPGRADE_DEFILER::ChooseUpgrade(void* data)
{
	if(BWAPI::Broodwar->self()->isResearching(BWAPI::TechTypes::Consume))
	{
		return BT_NODE::RUNNING;
	}

	if (BWAPI::Broodwar->self()->isResearchAvailable(BWAPI::TechTypes::Consume)) {
		BWAPI::UnitType researchType = BWAPI::TechTypes::Consume.whatResearches();
		std::vector<BWAPI::Unit> units;
		Tools::GetAllUnitsOfType(researchType, units);
		for (auto unit : units)
		{
			if (unit->isIdle()) {
				unit->research(BWAPI::TechTypes::Consume);
				return BT_NODE::SUCCESS;
			}
		}
	}

	if(BWAPI::Broodwar->self()->isResearching(BWAPI::TechTypes::Plague))
	{
		return BT_NODE::RUNNING;
	}

	if (BWAPI::Broodwar->self()->isResearchAvailable(BWAPI::TechTypes::Plague)) {
		BWAPI::UnitType researchType = BWAPI::TechTypes::Plague.whatResearches();
		std::vector<BWAPI::Unit> units;
		Tools::GetAllUnitsOfType(researchType, units);
		for (auto unit : units)
		{
			if (unit->isIdle()) {
				unit->research(BWAPI::TechTypes::Plague);
				return BT_NODE::SUCCESS;
			}
		}
	}

	if (BWAPI::Broodwar->self()->isUpgrading(BWAPI::UpgradeTypes::Metasynaptic_Node))
	{
		return BT_NODE::RUNNING;
	}

	int metasynapticNodeLevel = BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Metasynaptic_Node);
	int metasynapticNodeMaxLevel = BWAPI::Broodwar->self()->getMaxUpgradeLevel(BWAPI::UpgradeTypes::Metasynaptic_Node);

	if (metasynapticNodeLevel < metasynapticNodeMaxLevel) {
		BWAPI::UnitType upgradeType = BWAPI::UpgradeTypes::Metasynaptic_Node.whatUpgrades();
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

	return BT_NODE::FAILURE;
}
