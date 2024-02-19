#include "BT_ACTION_BUILD.h"
#include "Tools.h"
#include "Blackboard.h"

BT_ACTION_BUILD::BT_ACTION_BUILD(std::string name, BWAPI::UnitType building, BWAPI::TilePosition &tilePos, BT_NODE* parent, bool duplicate)
    : BT_ACTION(name, parent), m_building(building),m_tilePos(tilePos),m_duplicate(duplicate) {
}

BT_NODE::State BT_ACTION_BUILD::Evaluate(void* data)
{
    return ReturnState(Build(data));
}

std::string BT_ACTION_BUILD::GetDescription()
{
    return "BUILD ?";
}


BT_NODE::State BT_ACTION_BUILD::Build(void* data)
{
    Blackboard* pData = (Blackboard*)data;

    if (pData->currMinerals < m_building.mineralPrice())
    {
        std::cout <<"minerals < price" << std::endl;
		return BT_NODE::FAILURE;
	}

    bool startedBuilding = Tools::BuildBuildingAtPosition(m_building, m_tilePos, m_duplicate);

    return startedBuilding ? BT_NODE::SUCCESS : BT_NODE::FAILURE;
}