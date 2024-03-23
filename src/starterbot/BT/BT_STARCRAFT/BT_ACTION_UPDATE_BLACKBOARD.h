#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
template <typename T>
class BT_ACTION_UPDATE_BLACKBOARD : public BT_ACTION {
public:
    BT_ACTION_UPDATE_BLACKBOARD(std::string name, T& ref, T value, BT_NODE* parent);

private:
    T& m_ref_to_blackboard;
    T m_value_to_assign;

    BT_NODE::State Evaluate(void* data) override;
    std::string GetDescription() override;
};
//----------