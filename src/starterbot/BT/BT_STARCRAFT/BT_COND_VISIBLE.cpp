#include "BT_COND_VISIBLE.h"
#include "Tools.h"
#include "Blackboard.h"

BT_COND_VISIBLE::BT_COND_VISIBLE(std::string name, BWAPI::TilePosition &tilePos, BT_NODE* parent)
    : BT_CONDITION(name, parent, 0), m_tilePos(tilePos) {}

BT_NODE::State BT_COND_VISIBLE::Evaluate(void* data)
{
    if (m_tilePos == BWAPI::TilePositions::None)
    {
		return BT_NODE::FAILURE;
	}
    else if (BWAPI::Broodwar->isVisible(m_tilePos))
	{
        std::cout << m_tilePos << "BT_COND_VISIBLE::" << BWAPI::Broodwar->isVisible(m_tilePos) << std::endl;
        return BT_NODE::SUCCESS;
    }
    else
    {
		return BT_NODE::FAILURE;
	}
}

std::string BT_COND_VISIBLE::GetDescription()
{
    return "BUILD SUPPLY PROVIDER";
}