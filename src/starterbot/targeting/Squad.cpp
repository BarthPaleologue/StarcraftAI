#include "Squad.h"

Squad::Squad()
{
}

Squad::~Squad()
{
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




