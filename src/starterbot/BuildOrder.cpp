#include "BuildOrder.h"
#include "BuildOrderTools.h"
#include "Blackboard.h"
#include <iostream>

using namespace BuildOrderTools;

BuildOrder::BuildOrder() {
	// see https://liquipedia.net/starcraft/9_Pool_(vs._Terran)
	m_order = {
		{isSupplyTimingReached(9), BWAPI::UnitTypes::Zerg_Spawning_Pool, e_orderItemAction::Build},
		{isSupplyTimingReached(8), BWAPI::UnitTypes::Zerg_Drone, e_orderItemAction::Train},
		{isSupplyTimingReached(9), BWAPI::UnitTypes::Zerg_Extractor, e_orderItemAction::Build},
		{isSupplyTimingReached(8), BWAPI::UnitTypes::Zerg_Drone, e_orderItemAction::Train},
		{isSupplyTimingReached(9), BWAPI::UnitTypes::Zerg_Extractor, e_orderItemAction::Cancel},
		{isSupplyTimingReached(9), BWAPI::UnitTypes::Zerg_Overlord, e_orderItemAction::Train}
	};

	// see https://liquipedia.net/starcraft/12_Hatch_(vs._Protoss)
	/*m_order = {
		{ isSupplyTimingReached(9), BWAPI::UnitTypes::Zerg_Overlord, e_orderItemAction::Train },
		{ isSupplyTimingReached(12), BWAPI::UnitTypes::Zerg_Hatchery, e_orderItemAction::Build },
		{ isSupplyTimingReached(11), BWAPI::UnitTypes::Zerg_Spawning_Pool, e_orderItemAction::Build },
	};*/

	// https://liquipedia.net/starcraft/4/5_Pool
	/*m_order = {
		{isSupplyTimingReached(4), BWAPI::UnitTypes::Zerg_Spawning_Pool, e_orderItemAction::Build},
		{isSupplyTimingReached(3), BWAPI::UnitTypes::Zerg_Drone, e_orderItemAction::Train}
	};*/
}

void BuildOrder::nextTask()
{
	m_currentOrderIndex++;
	m_isCurrTaskStarted = false;
}

int BuildOrder::getCurrentIndex() {
	return m_currentOrderIndex;
}


int BuildOrder::getSize() {
	return m_order.size();
}

/// <summary>
/// Checks the current supply against the next stage of the build order. If the supply is enough, the next stage of the build order is executed (return true)
/// In the eventuality that the supply is not enough, nothing is done (return false)
/// </summary>
bool BuildOrder::evaluate(std::queue<BWAPI::UnitType>& _unitsRequested) {
	// avoid segfault if the build order is finished
	if (isFinished()) {
		return false;
	}
	const OrderItem& currentItem = m_order[m_currentOrderIndex];

	// timing not reached, exit the function (if task is started, might decrease in supply bc of drone morphed)
	if (!currentItem.conditionForStep() && !m_isCurrTaskStarted) return false;

	//std::cout << "evaluation of build order: step " << m_currentOrderIndex << std::endl;
	bool actionSuccess = false;
	switch (currentItem.action) {
	case e_orderItemAction::Build:
		if (!m_isCurrTaskStarted) {
			m_isCurrTaskStarted = true;
			_unitsRequested.push(currentItem.unitType);
		}
		//std::cout << "check if build " << currentItem.unitType << std::endl;
		if (isBuildingStarted(currentItem.unitType)) { // building has started
			//std::cout << "building " << currentItem.unitType << "has started" << std::endl;
			_unitsRequested.pop();
			actionSuccess = true;
			break;
		}
		
		//TODO: add a "if Hatchery"
		Tools::BuildBuilding(currentItem.unitType);
		break;
	case e_orderItemAction::Cancel:
		if (cancelConstruction(currentItem.unitType)) {
			actionSuccess = true;
		}
		break;
	case e_orderItemAction::Train:
		if (!m_isCurrTaskStarted) {
			m_isCurrTaskStarted = true;
			_unitsRequested.push(currentItem.unitType);
		}
		if (trainUnit(currentItem.unitType)) {
			_unitsRequested.pop();
			actionSuccess = true;
		}
		break;
	default:
		std::cout << "Error: unexpected orderItemAction" << std::endl;
		break;
	}

	if (actionSuccess) {
		nextTask();
	}
	return true;
}

bool BuildOrder::isFinished() {
	return m_currentOrderIndex >= m_order.size();
}