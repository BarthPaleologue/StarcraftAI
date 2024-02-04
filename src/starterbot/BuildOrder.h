#pragma once

#include "BWAPI.h"
#include "Tools.h"

enum OrderItemAction {
	Build,
	Cancel
};

struct OrderItem {
	int requiredSupply;
	BWAPI::UnitType unitType;
	OrderItemAction action;

	std::string toString() {
		std::stringstream stream;
		stream << "Required " << requiredSupply << " to " << action << " " << unitType;

		std::string resultString;
		stream >> resultString;

		return resultString;
	}
};

class BuildOrder
{
public:
	BuildOrder() {
		// see https://liquipedia.net/starcraft/9_Pool_(vs._Terran)
		m_order = {
			{9, BWAPI::UnitTypes::Zerg_Spawning_Pool, Build},
			{8, BWAPI::UnitTypes::Zerg_Drone, Build},
			{9, BWAPI::UnitTypes::Zerg_Extractor, Build},
			{8, BWAPI::UnitTypes::Zerg_Drone, Build},
			{9, BWAPI::UnitTypes::Zerg_Extractor, Cancel},
			{8, BWAPI::UnitTypes::Zerg_Overlord, Build}
		};
	}

	/// <summary>
	/// Checks the current supply against the next stage of the build order. If the supply is enough, the next stage of the build order is executed (return true)
	/// In the eventuality that the supply is not enough, nothing is done (return false)
	/// </summary>
	bool evaluate() {
		// Returns supply times 2, take divide 2 to get in game supply
		const int supply = BWAPI::Broodwar->self()->supplyUsed();
		//std::cout << "Supply: " << (supply / 2) << "\n";
		const int inGameSupply = supply / 2;

		const OrderItem currentItem = m_order[_currentOrderIndex];

		const int currentSupplyThreshold = currentItem.requiredSupply;

		// the supply is not enough, exit the function
		if (inGameSupply < currentSupplyThreshold) return false;

		switch (currentItem.action) {
		case Build:
			Tools::BuildBuilding(currentItem.unitType);
			break;
		case Cancel:
			// how do we cancel the current build of the given item?
			break;
		}

		_currentOrderIndex++;
		return true;
	}

	void debug() {
		for (int i = 0; i < m_order.size(); i++) {
			if (i == _currentOrderIndex) {
				std::cout << ">>>>> ";
			}
			else {
				std::cout << "----- ";
			}

			std::cout << i << " " << m_order[i].toString() << std::endl;
		}
	}

private:

	// this is the structure that holds the build order. In a sequence we have the required supply and unit of each stage of the build order
	std::vector<OrderItem> m_order;

	int _currentOrderIndex = 0;
};

