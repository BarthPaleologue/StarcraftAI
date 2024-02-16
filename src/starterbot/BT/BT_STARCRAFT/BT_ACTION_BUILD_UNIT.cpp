#pragma once // this is important because the template header will include the cpp and the cpp will try to include the template again
#include "BT_ACTION_BUILD_UNIT.h"
#include "Tools.h"
#include "Blackboard.h"
#include <typeinfo>


BT_ACTION_BUILD_UNIT::BT_ACTION_BUILD_UNIT(std::string name, BWAPI::UnitType unitType, BT_NODE* parent)
	: BT_ACTION(name, parent), m_unitType(unitType) {
}

BT_NODE::State BT_ACTION_BUILD_UNIT::Evaluate(void* data)
{
	return ReturnState(buildUnit(data));
}

std::string BT_ACTION_BUILD_UNIT::GetDescription()
{
	return "BUILD " + m_unitType;
}

BT_NODE::State BT_ACTION_BUILD_UNIT::buildUnit(void* data)
{
	Blackboard* pData = (Blackboard*)data;

	const bool startedBuilding = Tools::BuildBuilding(m_unitType);

	if (startedBuilding)
		BWAPI::Broodwar->printf("Started Building %s", m_unitType);

	return startedBuilding ? BT_NODE::SUCCESS : BT_NODE::FAILURE;
}