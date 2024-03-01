#include "BT_DECO_CONDITION_NOT_ENOUGH_OVERLORDS.h"

#include "Tools.h"
#include "Blackboard.h"

BT_DECO_CONDITION_NOT_ENOUGH_OVERLORDS::BT_DECO_CONDITION_NOT_ENOUGH_OVERLORDS(std::string name, BT_NODE* parent)
	: BT_DECO_CONDITION(name, parent, IsThereNotEnoughOverlords) {}

std::string BT_DECO_CONDITION_NOT_ENOUGH_OVERLORDS::GetDescription()
{
	return "BT_DECO_CONDITION_NOT_ENOUGH_OVERLORDS";
}

bool BT_DECO_CONDITION_NOT_ENOUGH_OVERLORDS::IsThereNotEnoughOverlords(void* data)
{
	const Blackboard* pBlackboard = (Blackboard*)data;

	const int totalUnitSupply = Tools::GetTotalSupply(true);

	const int overlordTrainingTime = BWAPI::UnitTypes::Zerg_Overlord.buildTime();
	const int focusedTrainedUnitTrainingTime = pBlackboard->focusedTrainingUnit.buildTime();

	const int focusedTrainedUnitSupply = pBlackboard->focusedTrainingUnit.supplyRequired();

	// number of bases we have
	const int nbBases = BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Zerg_Hatchery) +
		BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Zerg_Lair) +
		BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Zerg_Hive);

	const int unusedSupply = Tools::GetTotalSupply(true) - BWAPI::Broodwar->self()->supplyUsed();

	return (float)unusedSupply < (float)nbBases * (float)focusedTrainedUnitSupply * (float)overlordTrainingTime / (float)focusedTrainedUnitTrainingTime;
}
