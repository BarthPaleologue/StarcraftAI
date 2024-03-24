#pragma once

#include <BWAPI.h>

class Squad
{
public:
	Squad();

	~Squad();

	void attack(BWAPI::Unit target);

	void addUnit(BWAPI::Unit unit);
	
	void removeUnit(BWAPI::Unit unit);

	void moveTo(BWAPI::Position position);
	
	BWAPI::Unitset getUnits();

	BWAPI::Position getPosition();
	
	bool containsUnit(BWAPI::Unit unit);

	BWAPI::Unit getLastTarget();

	BWAPI::Unitset getEnemyUnitsInRadius(int radius);
	
	bool isEmpty();
	
	void clear();
	
	int getNbUnits();

private:
	BWAPI::Unitset m_unitSet{};

	BWAPI::Unit m_lastTarget = nullptr;
};

