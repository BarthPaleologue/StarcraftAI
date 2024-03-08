#include "BT_ACTION_TRAIN_UNIT.h"
#include "Tools.h"
#include "Blackboard.h"
#include <typeinfo>


BT_ACTION_TRAIN_UNIT::BT_ACTION_TRAIN_UNIT(std::string name, BWAPI::UnitType unitType, bool trainAsMuchAsPossible, BT_NODE* parent)
	: BT_ACTION(name, parent), m_unitType(unitType), m_trainAsMuchAsPossible(trainAsMuchAsPossible) {
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
	
	// finding all lavas
	std::vector<BWAPI::Unit> larvas;
	Tools::GetAllUnitsOfType(BWAPI::UnitTypes::Zerg_Larva, larvas);

	// filtering to only get larvas that are not morphing
	std::vector<BWAPI::Unit> larvasNotMorphing;
	for (auto larva : larvas) {
		if (larva->isMorphing()) continue;
		larvasNotMorphing.push_back(larva);
	}

	// if there are no available larvas, nothing happens
	if (larvas.empty()) {
		return BT_NODE::FAILURE;
	}

	// morph all larvas if as much as possible is true
	if (m_trainAsMuchAsPossible) {
		for (auto larva : larvas) {
			larva->morph(m_unitType);
			BWAPI::Error error = BWAPI::Broodwar->getLastError();
			if (error != BWAPI::Errors::None) {
				return BT_NODE::FAILURE;
			}
		}
	}
	// only train one larva in the other case
	else {
		larvas[0]->morph(m_unitType);
		BWAPI::Error error = BWAPI::Broodwar->getLastError();
		if (error != BWAPI::Errors::None) {
			return BT_NODE::FAILURE;
		}
	}

	return BT_NODE::FAILURE;
}