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

BWAPI::Unitset Squad::getUnits()
{
	return m_unitSet;
}

bool Squad::containsUnit(BWAPI::Unit unit)
{
	for (auto& u : m_unitSet) {
		if (u == unit) {
			return true;
		}
	}
	return false;
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




