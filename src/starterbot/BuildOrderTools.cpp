#include "BuildOrderTools.h"

//[[deprecated("use isTimingReached instead")]]
std::function<bool()> isSupplyTimingReached(int _supplyTiming) {
	return [_supplyTiming]() {
		// Returns supply times 2, take divide 2 to get in game supply
		const int supply = BWAPI::Broodwar->self()->supplyUsed();
		//std::cout << "Supply: " << (supply / 2) << "\n";
		const int inGameSupply = supply / 2;
		return inGameSupply >= _supplyTiming;
	};
}

std::function<bool()> isTimingReached(e_buildOrderTimingType _type, int _timing) {
	return [_timing, _type]() {
		// Returns supply times 2, take divide 2 to get in game supply
		int inGameValue = 0;
		switch (_type) {
		case buildOrderTiming_SUPPLY:
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