#pragma once

#include "BWAPI.h"
#include "Tools.h"
#include <functional> // to have function as attribute
#include <queue>

enum class e_orderItemAction {
	Build, // Build the unit type
	Cancel, // Cancel the build process of the unit type
	Train
};

struct OrderItem {
	std::function<bool()> conditionForStep; // this int is for humans a readable thing (supply count, building HP, etc)
	// #TODO: replace this with a job (could be scouting, cancelling, building somewhere, anything)
	BWAPI::UnitType unitType;

	// The action to perform with the given unitType in the OrderItem struct
	e_orderItemAction action;

	// #rewrite
	/*std::string toString() const{
		std::stringstream stream;
		stream << "Required " << requiredSupply << " to " << action << " " << unitType;

		std::string resultString;
		stream >> resultString;

		return resultString;
	}*/
};

class BuildOrder
{
public:
	BuildOrder();

	void nextTask();
	bool evaluate(std::queue<BWAPI::UnitType>& _unitsRequested);

	bool isFinished();

	/// <summary>
	/// Returns the current index of the build order
	/// </summary>
	/// <returns></returns>
	int getCurrentIndex();

	/// <summary>
	/// Returns the number of items in the build order
	/// </summary>
	/// <returns></returns>
	int getSize();

	// #rewrite
	//void debug() const {
	//	for (int i = 0; i < m_order.size(); i++) {
	//		if (i == m_currentOrderIndex) {
	//			std::cout << ">>>>> ";
	//		}
	//		else {
	//			std::cout << "----- ";
	//		}

	//		std::cout << i << " " << m_order[i].toString() << std::endl;
	//	}
	//}

private:
	// This array holds the sequence of actions of the build order.
	std::vector<OrderItem> m_order;

	// the current stage index of the build order
	int m_currentOrderIndex = 0;
	bool m_isCurrTaskStarted = false;
};

