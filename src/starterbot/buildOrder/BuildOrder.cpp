#include "BuildOrder.h"
#include "BuildOrderTools.h"
#include <iostream>
#include <Blackboard.h>

using namespace BuildOrderTools;

BuildOrder::BuildOrder(BuildOrderType _boType): m_buildOrderType(_boType) {
	switch (_boType) {
	case(BuildOrderType::NINE_POOL):
		m_order = {
			{isSupplyTimingReached(8), BWAPI::UnitTypes::Zerg_Drone, OrderItemAction::TRAIN},
			{isSupplyTimingReached(9), BWAPI::UnitTypes::Zerg_Extractor, OrderItemAction::BUILD},
			{isSupplyTimingReached(8), BWAPI::UnitTypes::Zerg_Drone, OrderItemAction::TRAIN},
			{isSupplyTimingReached(9), BWAPI::UnitTypes::Zerg_Extractor, OrderItemAction::CANCEL},
			// 8 zerglings
			{isSupplyTimingReached(9), BWAPI::UnitTypes::Zerg_Zergling, OrderItemAction::TRAIN},
			{isSupplyTimingReached(9), BWAPI::UnitTypes::Zerg_Zergling, OrderItemAction::TRAIN},
			{isSupplyTimingReached(9), BWAPI::UnitTypes::Zerg_Zergling, OrderItemAction::TRAIN},
			{isSupplyTimingReached(9), BWAPI::UnitTypes::Zerg_Zergling, OrderItemAction::TRAIN},
		};
		break;
	case(BuildOrderType::TWELVE_HATCH):
		m_order = {
			{ isSupplyTimingReached(9), BWAPI::UnitTypes::Zerg_Overlord, OrderItemAction::TRAIN },
			{ isSupplyTimingReached(12), BWAPI::UnitTypes::Zerg_Hatchery, OrderItemAction::BUILD },
			{ isSupplyTimingReached(11), BWAPI::UnitTypes::Zerg_Spawning_Pool, OrderItemAction::BUILD },
		};
		break;
	case(BuildOrderType::FOUR_POOL):
		m_order = {
			{isSupplyTimingReached(4), BWAPI::UnitTypes::Zerg_Spawning_Pool, OrderItemAction::BUILD},
			{isSupplyTimingReached(3), BWAPI::UnitTypes::Zerg_Drone, OrderItemAction::TRAIN},
			// fill the supply limit with zerglings
			{isSupplyTimingReached(4), BWAPI::UnitTypes::Zerg_Zergling, OrderItemAction::TRAIN},
			{isSupplyTimingReached(4), BWAPI::UnitTypes::Zerg_Zergling, OrderItemAction::TRAIN},
			{isSupplyTimingReached(4), BWAPI::UnitTypes::Zerg_Zergling, OrderItemAction::TRAIN},
			{isSupplyTimingReached(4), BWAPI::UnitTypes::Zerg_Zergling, OrderItemAction::TRAIN},
			{isSupplyTimingReached(4), BWAPI::UnitTypes::Zerg_Zergling, OrderItemAction::TRAIN},
		};
		break;

	default:
		//case(e_buildOrderType::DEBUG):
		m_order = {
			{isSupplyTimingReached(2), BWAPI::UnitTypes::Zerg_Hatchery, OrderItemAction::BUILD },
			{isSupplyTimingReached(9), BWAPI::UnitTypes::Zerg_Spawning_Pool, OrderItemAction::BUILD},
			{isSupplyTimingReached(8), BWAPI::UnitTypes::Zerg_Drone, OrderItemAction::TRAIN},
			{isSupplyTimingReached(99999), BWAPI::UnitTypes::Zerg_Drone, OrderItemAction::TRAIN},
		};
		break;
	}
}

BuildOrderType BuildOrder::getBuildOrderType() {
	return m_buildOrderType;
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
bool BuildOrder::evaluate(Blackboard* _pData) {
	std::queue<BWAPI::UnitType>& unitsRequested = _pData->unitsRequested;
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
	case OrderItemAction::BUILD:
		if (!m_isCurrTaskStarted) {
			m_isCurrTaskStarted = true;
			unitsRequested.push(currentItem.unitType);
		}
		//std::cout << "check if build " << currentItem.unitType << std::endl;
		if (isBuildingStarted(currentItem.unitType)) { // building has started
			//std::cout << "building " << currentItem.unitType << "has started" << std::endl;
			unitsRequested.pop();
			actionSuccess = true;
			break;
		}
		// build natural hatchery at natural position
		if (currentItem.unitType == BWAPI::UnitTypes::Zerg_Hatchery) {
			for (auto& baseTilePos : BASE_TILE_POS[_pData->myPosIdx]) {
				bool isBuilt = false;
				for (auto& unit : BWAPI::Broodwar->getUnitsOnTile(baseTilePos)) {
					if (unit->getType() == BWAPI::UnitTypes::Zerg_Hatchery) {
						isBuilt = true;
						break;
					}
				}
				if (isBuilt) continue;
				Tools::BuildBuildingAtPosition(BWAPI::UnitTypes::Zerg_Hatchery, baseTilePos);
				break;
			}
		}
		else if (currentItem.unitType == BWAPI::UnitTypes::Zerg_Spawning_Pool) {
			Tools::BuildBuildingAtPosition(BWAPI::UnitTypes::Zerg_Spawning_Pool, SPAWNING_POOL_TILE_POS[_pData->myPosIdx]);
		}
		else if (currentItem.unitType == BWAPI::UnitTypes::Zerg_Spire) {
			Tools::BuildBuildingAtPosition(BWAPI::UnitTypes::Zerg_Extractor, SPIRE_TILE_POS[_pData->myPosIdx]);
		}
		else if (currentItem.unitType == BWAPI::UnitTypes::Zerg_Sunken_Colony) {
			for (auto& unit : BWAPI::Broodwar->self()->getUnits()) {
				if (unit->getType() == BWAPI::UnitTypes::Zerg_Creep_Colony && unit->isCompleted()) {
					unit->morph(BWAPI::UnitTypes::Zerg_Sunken_Colony);
					break;
				}
			}
		}
		else {
			Tools::BuildBuilding(currentItem.unitType);
		}
		break;
	case OrderItemAction::CANCEL:
		if (cancelConstruction(currentItem.unitType)) {
			actionSuccess = true;
		}
		break;
	case OrderItemAction::TRAIN:
		if (!m_isCurrTaskStarted) {
			m_isCurrTaskStarted = true;
			unitsRequested.push(currentItem.unitType);
		}
		if (trainUnit(currentItem.unitType)) {
			unitsRequested.pop();
			actionSuccess = true;
		}
		break;
	default:
		std::cout << "Error: unexpected orderItemAction" << std::endl;
		break;
	}
	if (actionSuccess) {
		std::cout << currentItem.unitType << " successfully started" << std::endl;
		nextTask();
	}
	return true;
}

bool BuildOrder::isFinished() {
	return m_currentOrderIndex >= m_order.size();
}