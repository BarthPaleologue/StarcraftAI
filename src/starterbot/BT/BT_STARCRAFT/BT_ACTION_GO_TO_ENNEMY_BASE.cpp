#include "BT_ACTION_GO_TO_ENNEMY_BASE.h"
#include "Tools.h"
#include "Blackboard.h"

BT_ACTION_GO_TO_ENNEMY_BASE::BT_ACTION_GO_TO_ENNEMY_BASE(std::string name, BT_NODE* parent)
	: BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_GO_TO_ENNEMY_BASE::Evaluate(void* data)
{
	return ReturnState(GoToEnnemyBase(data));
}

std::string BT_ACTION_GO_TO_ENNEMY_BASE::GetDescription()
{
	return "GO TO ENNEMY BASE";
}

BT_NODE::State BT_ACTION_GO_TO_ENNEMY_BASE::GoToEnnemyBase(void* data)
{
	Blackboard* blackboard = (Blackboard*)data;

	// TODO

	// this should only happen if the depot is already training another kind of unit
	return BT_NODE::FAILURE;
}