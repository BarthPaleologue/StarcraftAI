#include "BT_ACTION_MUTALISK_SQUAD_CHOOSE_TARGET.h"
#include "Blackboard.h"

BT_ACTION_MUTALISK_SQUAD_CHOOSE_TARGET::BT_ACTION_MUTALISK_SQUAD_CHOOSE_TARGET(std::string name, Squad* squad, BT_NODE* parent)
	:BT_ACTION(name, parent)
{
}

BT_NODE::State BT_ACTION_MUTALISK_SQUAD_CHOOSE_TARGET::Evaluate(void* data)
{
	return ReturnState(ChooseTarget(data));
}

std::string BT_ACTION_MUTALISK_SQUAD_CHOOSE_TARGET::GetDescription()
{
	return "BT_ACTION_MUTALISK_SQUAD_CHOOSE_TARGET";
}

BT_NODE::State BT_ACTION_MUTALISK_SQUAD_CHOOSE_TARGET::ChooseTarget(void* data)
{
	Blackboard* blackboard = (Blackboard*)data;

	// find all enemies in range
	int mutaliskRange = BWAPI::UnitTypes::Hero_Kukulza_Mutalisk.airWeapon().maxRange();
	BWAPI::Unitset enemiesInRange = m_squad->getEnemyUnitsInRadius(mutaliskRange);

	// assign priority score to each enemy
	std::map<BWAPI::Unit, int> scores{};
	for (auto enemyUnit : enemiesInRange) {
		int score = blackboard->harassmentManager.getSquadTargetPriority(m_squad, enemyUnit);
		scores[enemyUnit] = score;
	}

	// sort by priority
	std::vector<std::pair<BWAPI::Unit, int>> sortedScores(scores.begin(), scores.end());
	std::sort(sortedScores.begin(), sortedScores.end(), [](const std::pair<BWAPI::Unit, int>& left, const std::pair<BWAPI::Unit, int>& right) {
		return left.second > right.second;
	});

	if (!sortedScores.empty()) {
		m_squad->setTarget(sortedScores[0].first);
		return BT_NODE::SUCCESS;
	}

	// no enemy in range, TODO: what should the squad do?
	return BT_NODE::SUCCESS;
}
