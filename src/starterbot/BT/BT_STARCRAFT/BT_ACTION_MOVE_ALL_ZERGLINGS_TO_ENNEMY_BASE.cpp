#include "BT_ACTION_MOVE_ALL_ZERGLINGS_TO_ENNEMY_BASE.h"
#include "Tools.h"
#include "Blackboard.h"

BT_ACTION_MOVE_ALL_ZERGLINGS_TO_ENNEMY_BASE::BT_ACTION_MOVE_ALL_ZERGLINGS_TO_ENNEMY_BASE(std::string name, BT_NODE* parent)
	: BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_MOVE_ALL_ZERGLINGS_TO_ENNEMY_BASE::Evaluate(void* data)
{
	return ReturnState(GoToEnnemyBase(data));
}

std::string BT_ACTION_MOVE_ALL_ZERGLINGS_TO_ENNEMY_BASE::GetDescription()
{
	return "ALL ZERGLINGS GO TO ENNEMY BASE";
}

BT_NODE::State BT_ACTION_MOVE_ALL_ZERGLINGS_TO_ENNEMY_BASE::GoToEnnemyBase(void* data)
{
	Blackboard* blackboard = (Blackboard*)data;

	if (!blackboard->ennemyBasesPositions.empty()) {
		// we found at least one ennemy base
		BWAPI::Position tilePosition = blackboard->ennemyBasesPositions[0];

		std::vector<BWAPI::Unit> zerglings;
		Tools::GetAllUnitsOfType(BWAPI::UnitTypes::Zerg_Zergling, zerglings);

		for (auto zergling : zerglings) {
			zergling->move(tilePosition);
		}

		return BT_NODE::SUCCESS;
	}

	return BT_NODE::FAILURE;
}