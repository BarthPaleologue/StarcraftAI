#pragma once
#include "BT_DECO_CONDITION.h"
class BT_DECO_CONDITION_ALL_IN :
    public BT_DECO_CONDITION
{
public:
    BT_DECO_CONDITION_ALL_IN(std::string name, BT_NODE* parent);

    std::string GetDescription() override;

    static bool IsAllIn(void* data);

};

