#include "BuildOrder.h"

std::function<bool()> isSupplyTimingReached(int supplyTiming) {
	return [supplyTiming]() {
		// Returns supply times 2, take divide 2 to get in game supply
		const int supply = BWAPI::Broodwar->self()->supplyUsed();
		//std::cout << "Supply: " << (supply / 2) << "\n";
		const int inGameSupply = supply / 2;
		return inGameSupply >= supplyTiming;
	};
}

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
bool BuildOrder::evaluate(){
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