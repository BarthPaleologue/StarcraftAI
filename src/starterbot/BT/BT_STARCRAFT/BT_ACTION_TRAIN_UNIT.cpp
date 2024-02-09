#include "BT_ACTION_TRAIN_UNIT.h"
#include "Tools.h"
#include "Blackboard.h"

BT_ACTION_TRAIN_UNIT::BT_ACTION_TRAIN_UNIT(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_TRAIN_UNIT::Evaluate(void* data)
{
    return ReturnState(TrainUnit(data));
}

std::string BT_ACTION_TRAIN_UNIT::GetDescription()
{
    return "TRAIN UNIT";
}


/// <summary>
/// This function chooses a unit to train and trains it if possible
/// </summary>
/// <param name="data"></param>
/// <returns></returns>
BT_NODE::State BT_ACTION_TRAIN_UNIT::TrainUnit(void* data)
{
    Blackboard* blackboard = (Blackboard*)data;

    // find a valid depot
    const BWAPI::Unit myDepot = Tools::GetDepot();

    // if the build order is complete, then we train zerglings
    if (blackboard->buildOrder.isFinished()) {
        if (myDepot->isTraining()) {
            return BT_NODE::RUNNING;
        }

        myDepot->train(BWAPI::UnitTypes::Zerg_Zergling);

        BWAPI::Error error = BWAPI::Broodwar->getLastError();
        if (error != BWAPI::Errors::None) {
            return BT_NODE::FAILURE;
        }

        return BT_NODE::SUCCESS;
    }

    return BT_NODE::FAILURE;
}