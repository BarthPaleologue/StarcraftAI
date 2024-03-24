#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

template <typename T>
class BT_ACTION_UPDATE_BLACKBOARD : public BT_ACTION {
public:

    template <typename T>
    BT_ACTION_UPDATE_BLACKBOARD(std::string name, T& ref, T value, BT_NODE* parent)
        : BT_ACTION(name, parent), m_value_to_assign(value), m_ref_to_blackboard(ref) {
    }

private:
    T& m_ref_to_blackboard;
    T m_value_to_assign;

    template <typename T>
    BT_NODE::State Evaluate(void* data) {
        //Blackboard* pData = (Blackboard*)data;
        m_ref_to_blackboard = m_value_to_assign;
        return BT_NODE::SUCCESS;
    }


    std::string GetDescription() {
        return "ACTION_UPDATE_BLACKBOARD";
    }
};