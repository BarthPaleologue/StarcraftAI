#include "BT_DECO_CONDITION_ALL_IN.h"
#include "Blackboard.h"

BT_DECO_CONDITION_ALL_IN::BT_DECO_CONDITION_ALL_IN(std::string name, BT_NODE* parent)
	: BT_DECO_CONDITION(name, parent, IsAllIn) {}

std::string BT_DECO_CONDITION_ALL_IN::GetDescription()
{
	return "BT_DECO_CONDITION_ALL_IN";
}

bool BT_DECO_CONDITION_ALL_IN::IsAllIn(void* data)
{
	Blackboard* blackboard = (Blackboard*)data;

	return blackboard->canAllIn();
}
