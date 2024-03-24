#include "BT_DECO_CONDITION_CANT_WIN.h"
#include "Blackboard.h"

BT_DECO_CONDITION_CANT_WIN::BT_DECO_CONDITION_CANT_WIN(std::string name, BT_NODE* parent)
	: BT_DECO_CONDITION(name, parent, IsCantWIn) {}

std::string BT_DECO_CONDITION_CANT_WIN::GetDescription()
{
	return "BT_DECO_CONDITION_CANT_WIN";
}

bool BT_DECO_CONDITION_CANT_WIN::IsCantWIn(void* data)
{
	Blackboard* blackboard = (Blackboard*)data;

	return blackboard->cantWin();
}
