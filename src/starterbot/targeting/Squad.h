#pragma once

#include <BWAPI.h>

/// <summary>
/// A squad is a wrapper around a BWAPI::Unitset that provides additional functionality
/// </summary>
class Squad
{
public:
	Squad();

	~Squad();

	/// <summary>
	/// Make all the units in the squad attack the target
	/// </summary>
	/// <param name="target">The enemy unit that will be attacked</param>
	void attack(BWAPI::Unit target);

	/// <summary>
	/// Add a unit to the squad
	/// </summary>
	/// <param name="unit">The unit to be added</param>
	void addUnit(BWAPI::Unit unit);
	
	/// <summary>
	/// Remove a unit from the squad
	/// </summary>
	/// <param name="unit">The unit to be removed</param>
	void removeUnit(BWAPI::Unit unit);

	/// <summary>
	/// Moves all the units in the squad to the specified position
	/// </summary>
	/// <param name="position">The destination of the squad</param>
	void moveTo(BWAPI::Position position);
	
	/// <summary>
	/// Return the underlying unit set
	/// </summary>
	/// <returns>The unit set of the squad</returns>
	BWAPI::Unitset getUnits();

	/// <summary>
	/// Returns the average position of the units in the squad
	/// </summary>
	/// <returns>The average position of the units in the squad</returns>
	BWAPI::Position getPosition();
	
	/// <summary>
	/// Returns true if the squad contains the specified unit
	/// </summary>
	/// <param name="unit">The unit to check</param>
	/// <returns>true if the unit is in the squad, false otherwise</returns>
	bool containsUnit(BWAPI::Unit unit);

	/// <summary>
	/// Finds all enemy units within a given radius
	/// </summary>
	/// <param name="radius">The radius to find enemy units into</param>
	/// <returns>A set of all enemy units in the given radius</returns>
	BWAPI::Unitset getEnemyUnitsInRadius(int radius);

	/// <summary>
	/// Set the target of the squad to the given unit
	/// This is later used in squad behavior trees to determine the target of the squad
	/// </summary>
	/// <param name="target"></param>
	void setTarget(BWAPI::Unit target);

	/// <summary>
	///	Returns the current target of the squad
	/// </summary>
	/// <returns>The current target of the squad</returns>
	BWAPI::Unit getTarget();

	/// <summary>
	/// Orders all the units in the squad to hold position
	/// </summary>
	void holdPosition();

	/// <summary>
	/// Return the average of the facing angles of the units in the squad
	/// </summary>
	/// <returns>The facing angle of the squad in radians</returns>
	double getFacingAngle();
	
	/// <summary>
	/// Returns true if the squad is empty
	/// </summary>
	/// <returns>True if the squad is empty, false otherwise</returns>
	bool isEmpty();
	
	/// <summary>
	/// Remove all units from the squad
	/// </summary>
	void clear();
	
	/// <summary>
	/// Return the number of units inside the squad
	/// </summary>
	/// <returns>The number of units inside the squad</returns>
	int getNbUnits();

private:
	BWAPI::Unitset m_unitSet{};

	BWAPI::Unit m_target = nullptr;
};

