#pragma once

#include <BWAPI.h>

class Squad
{
public:
	Squad();

	~Squad();

	void addUnit(BWAPI::Unit unit);
	
	void removeUnit(BWAPI::Unit unit);

	void moveTo(BWAPI::Position position);
	
	BWAPI::Unitset getUnits();
	
	bool containsUnit(BWAPI::Unit unit);
	
	bool isEmpty();
	
	void clear();
	
	int getNbUnits();

private:
	BWAPI::Unitset m_unitSet{};
};

