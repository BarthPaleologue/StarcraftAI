#include "BT_ACTION_TRAIN_UNIT.h"
#include "Tools.h"
#include "Blackboard.h"
#include <typeinfo>


BT_ACTION_TRAIN_UNIT::BT_ACTION_TRAIN_UNIT(std::string name, BWAPI::UnitType unitType, BT_NODE* parent)
	: BT_ACTION(name, parent), m_unitType(unitType) {
}

BT_NODE::State BT_ACTION_TRAIN_UNIT::Evaluate(void* data)
{
	return ReturnState(TrainUnit(data));
}

std::string BT_ACTION_TRAIN_UNIT::GetDescription()
{
	return "TRAIN " + m_unitType;
}

BT_NODE::State BT_ACTION_TRAIN_UNIT::TrainUnit(void* data)
{
	Blackboard* pData = (Blackboard*)data;

    const BWAPI::Unit myDepot = Tools::GetDepot();

    // if we have a valid depot unit and it's currently not training something, train a worker
    // there is no reason for a bot to ever use the unit queueing system, it just wastes resources
    if (myDepot && !myDepot->isTraining()) {
        myDepot->train(m_unitType);
        BWAPI::Error error = BWAPI::Broodwar->getLastError();
        if (error != BWAPI::Errors::None) {
            return BT_NODE::FAILURE;
        }
        else return BT_NODE::SUCCESS;
    }

    return BT_NODE::FAILURE;
}