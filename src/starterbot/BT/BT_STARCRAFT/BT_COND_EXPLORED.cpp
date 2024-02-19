#include "BT_COND_EXPLORED.h"
#include "Tools.h"
#include "Blackboard.h"

BT_COND_EXPLORED::BT_COND_EXPLORED(std::string name, BWAPI::TilePosition &tilePos, BT_NODE* parent)
    : BT_CONDITION(name, parent, 0), m_tilePos(tilePos) {}

BT_NODE::State BT_COND_EXPLORED::Evaluate(void* data)
{
    if (m_tilePos == BWAPI::TilePositions::None)
    {
		return BT_NODE::FAILURE;
	}
    else if (BWAPI::Broodwar->isVisible(m_tilePos))
	{
        return BT_NODE::SUCCESS;
    }
    else
    {
		return BT_NODE::FAILURE;
	}
}

std::string BT_COND_EXPLORED::GetDescription()
{
    return "cond explored";
}