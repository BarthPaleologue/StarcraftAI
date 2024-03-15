#include "BuildOrderTools.h"
#include "Tools.h"

//[[deprecated("use isTimingReached instead")]]
std::function<bool()> BuildOrderTools::isSupplyTimingReached(int _supplyTiming) {
	return [_supplyTiming]() {
		// Returns supply times 2, take divide 2 to get in game supply
		const int supply = BWAPI::Broodwar->self()->supplyUsed();
		//std::cout << "Supply: " << (supply / 2) << "\n";
		const int inGameSupply = supply / 2;
		return inGameSupply >= _supplyTiming;
	};
}

std::function<bool()> BuildOrderTools::isTimingReached(e_buildOrderTimingType _type, int _timing) {
	return [_timing, _type]() {
		// Returns supply times 2, take divide 2 to get in game supply
		int inGameValue = 0;
		switch (_type) {
		case e_buildOrderTimingType::Supply:
			//std::cout << "Supply: " << (supply / 2) << "\n";
			inGameValue = BWAPI::Broodwar->self()->supplyUsed() / 2;
			break;
		default:
			inGameValue = 0;
			break;
		}
		return inGameValue >= _timing;
	};
}

bool BuildOrderTools::trainUnit(BWAPI::UnitType unitType) {

	const BWAPI::Unit myDepot = Tools::GetDepot();

	// if we have a valid depot (hatchery) and it's currently not training something, train a worker
	// there is no reason for a bot to ever use the unit queueing system, it just wastes resources
	if (myDepot && !myDepot->isTraining()) {
		myDepot->train(unitType);
		BWAPI::Error error = BWAPI::Broodwar->getLastError();
		if (error != BWAPI::Errors::None)
			return false;
		else return true;
	}
	return false;
}

BWAPI::Unit BuildOrderTools::findStartedBuilding(BWAPI::UnitType _unitType)
{
	// For each unit that we own
	for (auto& unit : BWAPI::Broodwar->self()->getUnits())
	{
		// if the unit is of the correct type, return it
		if (unit->getType() == _unitType) //&& unit->isCompleted())
		{
			//std::cout << "found a " << unit->getType() << std::endl;
			if (unit->isBeingConstructed())
				return unit;
		}
	}
	// If we didn't find a valid unit to return, make sure we return nullptr
	return nullptr;
}

bool BuildOrderTools::isBuildingStarted(BWAPI::UnitType _unitType) {
	return BuildOrderTools::findStartedBuilding(_unitType) != nullptr;
}

bool BuildOrderTools::cancelConstruction(BWAPI::UnitType _unitType) {
	BWAPI::Unit buildingToCancel = findStartedBuilding(_unitType);
	return buildingToCancel->cancelConstruction();
}