#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class BT_ACTION_BUILD : public BT_ACTION {
public:
    BT_ACTION_BUILD(std::string name, BWAPI::UnitType building, const BWAPI::TilePosition &tilePos, BT_NODE* parent);

private:
    BWAPI::UnitType m_building;
    BWAPI::TilePosition m_tilePos;
    bool m_duplicate;

    BT_NODE::State Evaluate(void* data) override;
    std::string GetDescription() override;
    BT_NODE::State Build(void* data);
};
//----------