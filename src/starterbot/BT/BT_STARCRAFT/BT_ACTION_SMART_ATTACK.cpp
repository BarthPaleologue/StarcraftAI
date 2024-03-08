#include "BT_ACTION_SMART_ATTACK.h"
#include "Tools.h"
#include "ForceTools.h"
#include "Blackboard.h"

BT_ACTION_SMART_ATTACK::BT_ACTION_SMART_ATTACK(std::string name, BWAPI::Unit unit, BT_NODE* parent)
	: BT_ACTION(name, parent), m_unit(unit) {}

BT_NODE::State BT_ACTION_SMART_ATTACK::Evaluate(void* data)
{
	return ReturnState(SmartAttack(data));
}

std::string BT_ACTION_SMART_ATTACK::GetDescription()
{
	return "GO TO ENEMY BASE";
}

BT_NODE::State BT_ACTION_SMART_ATTACK::SmartAttack(void* data)
{
	Blackboard* blackboard = (Blackboard*)data;

	BWAPI::Unitset ememyUnitsInRadius = Tools::GetUnitsInRadius(m_unit->getPosition(), 300, BWAPI::Broodwar->enemy()->getUnits());

	std::map<BWAPI::Unit, std::pair<float, float>> combatPredictions;
	for (auto& enemyUnit : ememyUnitsInRadius)
	{
		std::pair<float, float> prediction = ForceTools::fightPredictor(m_unit->getHitPoints(), m_unit->getType(), BWAPI::Broodwar->self(), enemyUnit->getHitPoints(), enemyUnit->getType(), BWAPI::Broodwar->enemy());
		combatPredictions[enemyUnit] = prediction;
	}

	// sort the predictions using the first value of the pair to get the best target
	std::vector<std::pair<BWAPI::Unit, std::pair<float, float>>> sortedPredictions(combatPredictions.begin(), combatPredictions.end());
	std::sort(sortedPredictions.begin(), sortedPredictions.end(), [](const std::pair<BWAPI::Unit, std::pair<float, float>>& left, const std::pair<BWAPI::Unit, std::pair<float, float>>& right) {
		return left.second.first < right.second.first;
	});

	if (!sortedPredictions.empty())
	{
		m_unit->attack(sortedPredictions[0].first);
		return BT_NODE::SUCCESS;
	}

	return BT_NODE::FAILURE;
}