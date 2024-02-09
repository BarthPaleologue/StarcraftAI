#pragma once
#include <cassert>
#include "BT_DECO_CONDITION.h"

class BT_DECO_CONDITION_BUILD_ORDER_FINISHED : public BT_DECO_CONDITION {
public:
    BT_DECO_CONDITION_BUILD_ORDER_FINISHED(std::string name, BT_NODE* parent);
    
    std::string GetDescription() override;

    static bool IsBuildOrderFinished(void* data);

};