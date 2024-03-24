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

	void setTarget(BWAPI::Unit target);

	BWAPI::Unit getTarget();

	void holdPosition();

	/// <summary>
	/// Return the average of the facing angles of the units in the squad
	/// </summary>
	/// <returns>The facing angle of the squad in radians</returns>
	double getFacingAngle();
	
	bool isEmpty();
	
	void clear();
	
	int getNbUnits();

private:
	BWAPI::Unitset m_unitSet{};

	BWAPI::Unit m_lastTarget = nullptr;
	BWAPI::Unit m_target = nullptr;
};

