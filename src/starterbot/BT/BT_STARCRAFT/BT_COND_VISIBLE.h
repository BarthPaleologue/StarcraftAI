#pragma once
#include <cassert>
#include "BT_CONDITION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class BT_COND_VISIBLE : public BT_CONDITION {
public:
    BT_COND_VISIBLE(std::string name, BWAPI::TilePosition &tilePos, BT_NODE* parent);

private:
    BWAPI::TilePosition &m_tilePos;

    State Evaluate(void* data) override;
    std::string GetDescription() override;
};
//----------