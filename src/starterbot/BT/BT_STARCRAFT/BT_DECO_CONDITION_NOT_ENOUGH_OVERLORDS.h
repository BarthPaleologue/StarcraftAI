#pragma once
#include "BT_DECO_CONDITION.h"
class BT_DECO_CONDITION_NOT_ENOUGH_OVERLORDS :
    public BT_DECO_CONDITION
{
public:
	BT_DECO_CONDITION_NOT_ENOUGH_OVERLORDS(std::string name, BT_NODE* parent);
	std::string GetDescription() override;
	static bool IsThereNotEnoughOverlords(void *data);
};

