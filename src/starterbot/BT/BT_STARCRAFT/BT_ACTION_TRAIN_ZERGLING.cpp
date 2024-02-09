#include "BT_ACTION_TRAIN_ZERGLING.h"
#include "Tools.h"
#include "Blackboard.h"

BT_ACTION_TRAIN_ZERGLING::BT_ACTION_TRAIN_ZERGLING(std::string name, BT_NODE* parent)
	: BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_TRAIN_ZERGLING::Evaluate(void* data)
{
	return ReturnState(TrainZergling(data));
}

std::string BT_ACTION_TRAIN_ZERGLING::GetDescription()
{
	return "TRAIN ZERGLING";
}


/// <summary>
/// This function chooses a unit to train and trains it if possible
/// </summary>
/// <param name="data"></param>
/// <returns></returns>
BT_NODE::State BT_ACTION_TRAIN_ZERGLING::TrainZergling(void* data)
{
	Blackboard* blackboard = (Blackboard*)data;

	// find a valid depot
	const BWAPI::Unit myDepot = Tools::GetDepot();

	// if we could not find a valid depot, fail
	if (!myDepot) {
		return BT_NODE::FAILURE;
	}

	// if we are already training a zergling, the task is running
	if (myDepot->isTraining() && myDepot->getTrainingQueue()[0] == BWAPI::UnitTypes::Zerg_Zergling) {
		return BT_NODE::RUNNING;
	}

	// if the depot is free, train a new zergling
	if (!myDepot->isTraining()) {
		myDepot->train(BWAPI::UnitTypes::Zerg_Zergling);
		BWAPI::Error error = BWAPI::Broodwar->getLastError();
		if (error != BWAPI::Errors::None)
			return BT_NODE::FAILURE;
		else return BT_NODE::SUCCESS;
	}

	// this should only happen if the depot is already training another kind of unit
	return BT_NODE::FAILURE;
}