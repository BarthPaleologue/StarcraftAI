#include "Squad.h"

Squad::Squad()
{
}

Squad::~Squad()
{
}

void Squad::attack(BWAPI::Unit target)
{
	m_unitSet.attack(target);
}

void Squad::addUnit(BWAPI::Unit unit)
{
	m_unitSet.insert(unit);
}

void Squad::removeUnit(BWAPI::Unit unit)
{
	m_unitSet.erase(unit);
}

void Squad::moveTo(BWAPI::Position position)
{
	m_unitSet.move(position);
}

BWAPI::Position Squad::getPosition() {
	return m_unitSet.getPosition();
}

BWAPI::Unitset Squad::getUnits()
{
	return m_unitSet;
}

bool Squad::containsUnit(BWAPI::Unit unit)
{
	return m_unitSet.contains(unit);
}

BWAPI::Unitset Squad::getEnemyUnitsInRadius(int radius)
{
	BWAPI::Unitset unitsInRadius = m_unitSet.getUnitsInRadius(radius);
	// Remove units that are not enemies
	BWAPI::Unitset enemyUnitsInRadius;
	for (auto unit : unitsInRadius) {
		if (unit->getPlayer() != BWAPI::Broodwar->self()) {
			enemyUnitsInRadius.insert(unit);
		}
	}
	return enemyUnitsInRadius;
}

void Squad::setTarget(BWAPI::Unit target)
{
	m_target = target;
}

BWAPI::Unit Squad::getTarget()
{
	return m_target;
}

void Squad::holdPosition()
{
	m_unitSet.holdPosition();
}

double Squad::getFacingAngle()
{
	double sum = 0;
	for (auto& unit : m_unitSet) {
		sum += unit->getAngle();
	}
	return sum / m_unitSet.size();
}

bool Squad::isEmpty()
{
	return m_unitSet.empty();
}

void Squad::clear()
{
	m_unitSet.clear();
}

int Squad::getNbUnits()
{
	return m_unitSet.size();
}




