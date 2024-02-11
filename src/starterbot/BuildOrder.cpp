#include "BuildOrder.h"
#include "BuildOrderTools.h"
#include "Blackboard.h"
#include <iostream>

using namespace BuildOrderTools;

BuildOrder::BuildOrder() {
	// see https://liquipedia.net/starcraft/9_Pool_(vs._Terran)
	m_order = {
		{isSupplyTimingReached(9), BWAPI::UnitTypes::Zerg_Spawning_Pool, e_orderItemAction::Build},
		//{isSupplyTimingReached(8), BWAPI::UnitTypes::Zerg_Drone, e_orderItemAction::Train},
		{isSupplyTimingReached(9), BWAPI::UnitTypes::Zerg_Extractor, e_orderItemAction::Build},
		//{isSupplyTimingReached(8), BWAPI::UnitTypes::Zerg_Drone, e_orderItemAction::Train},
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

	// timing not reached, exit the function
	if (!currentItem.conditionForStep()) return false;

	bool actionSuccess = false;
	switch (currentItem.action) {
	case e_orderItemAction::Build:
		_unitsRequested.push(currentItem.unitType); // with unordered_set, doesn't add duplicates
		if (isBuildingStarted(currentItem.unitType)) { // building has started
			_unitsRequested.pop();
			actionSuccess = true;
			break;
		}
		
		//TODO: add a "if Hatchery"
		Tools::BuildBuilding(currentItem.unitType);
		break;
	case e_orderItemAction::Cancel:
		// how do we cancel the current build of the given item?
		if (cancelConstruction(currentItem.unitType)) {
			actionSuccess = true;
		}
		break;
	case e_orderItemAction::Train:
		_unitsRequested.push(currentItem.unitType);
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
		m_currentOrderIndex++;
	}
	return true;
}

bool BuildOrder::isFinished() {
	return m_currentOrderIndex >= m_order.size();
}