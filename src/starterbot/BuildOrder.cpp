#include "BuildOrder.h"
#include "BuildOrderTools.h"

BuildOrder::BuildOrder() {
	// see https://liquipedia.net/starcraft/9_Pool_(vs._Terran)
	m_order = {
		{isSupplyTimingReached(9), BWAPI::UnitTypes::Zerg_Spawning_Pool, Build},
		{isSupplyTimingReached(8), BWAPI::UnitTypes::Zerg_Drone, Build},
		{isSupplyTimingReached(9), BWAPI::UnitTypes::Zerg_Extractor, Build},
		{isSupplyTimingReached(8), BWAPI::UnitTypes::Zerg_Drone, Build},
		{isSupplyTimingReached(9), BWAPI::UnitTypes::Zerg_Extractor, Cancel},
		{isSupplyTimingReached(9), BWAPI::UnitTypes::Zerg_Overlord, Build}
	};
}

/// <summary>
/// Checks the current supply against the next stage of the build order. If the supply is enough, the next stage of the build order is executed (return true)
/// In the eventuality that the supply is not enough, nothing is done (return false)
/// </summary>
bool BuildOrder::evaluate() {
	// avoid segfault if the build order is finished
	if (isFinished()) {
		return false;
	}
	const OrderItem& currentItem = m_order[m_currentOrderIndex];

	// timing not reached, exit the function
	if (!currentItem.conditionForStep()) return false;

	switch (currentItem.action) {
	case Build:
		Tools::BuildBuilding(currentItem.unitType);
		break;
	case Cancel:
		// how do we cancel the current build of the given item?
		break;
	}

	m_currentOrderIndex++;
	return true;
}

bool BuildOrder::isFinished() {
	return m_currentOrderIndex >= m_order.size();
}