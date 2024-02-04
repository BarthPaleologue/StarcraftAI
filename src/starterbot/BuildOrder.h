#pragma once

#include "BWAPI.h"
#include "Tools.h"
#include <functional> // to have function as attribute

enum OrderItemAction {
	Build,
	Cancel
};

struct OrderItem {
	std::function<bool()> conditionForStep; // this int is for humans a readable thing (supply count, building HP, etc)
	// #TODO: replace this with a job (could be scouting, cancelling, building somewhere, anything)
	BWAPI::UnitType unitType;
	OrderItemAction action;

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

	bool evaluate();

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
	// this is the structure that holds the build order. In a sequence we have the required supply and unit of each stage of the build order
	std::vector<OrderItem> m_order;
	int m_currentOrderIndex = 0;
};

