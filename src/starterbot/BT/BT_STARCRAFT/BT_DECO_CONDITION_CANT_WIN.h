#pragma once
#include "BT_DECO_CONDITION.h"
class BT_DECO_CONDITION_CANT_WIN :
    public BT_DECO_CONDITION
{
public:
    BT_DECO_CONDITION_CANT_WIN(std::string name, BT_NODE* parent);

    std::string GetDescription() override;

    static bool IsCantWIn(void* data);

};

