#include "BT_ACTION_BUILD.h"
#include "Tools.h"
#include "Blackboard.h"

BT_ACTION_BUILD::BT_ACTION_BUILD(std::string name, BWAPI::UnitType building, const BWAPI::TilePosition &tilePos, BT_NODE* parent)
    : BT_ACTION(name, parent), m_building(building),m_tilePos(tilePos) {
}

BT_NODE::State BT_ACTION_BUILD::Evaluate(void* data)
{
    return ReturnState(Build(data));
}

std::string BT_ACTION_BUILD::GetDescription()
{
    return "BUILD " + m_building;
}


BT_NODE::State BT_ACTION_BUILD::Build(void* data)
{
    Blackboard* pData = (Blackboard*)data;

    if (pData->currMinerals < m_building.mineralPrice())
    {
		return BT_NODE::FAILURE;
	}

    bool startedBuilding = (m_tilePos != NONE_POS) ?
        Tools::BuildBuildingAtPosition(m_building, m_tilePos)
        : Tools::BuildBuilding(m_building);

    return startedBuilding ? BT_NODE::SUCCESS : BT_NODE::FAILURE;
}