#include "BT_ACTION_MUTALISK_SQUAD_ATTACK.h"

BT_ACTION_MUTALISK_SQUAD_ATTACK::BT_ACTION_MUTALISK_SQUAD_ATTACK(std::string name, Squad* squad, BT_NODE* parent)
	: BT_ACTION(name, parent), m_squad(squad)
{
}

BT_NODE::State BT_ACTION_MUTALISK_SQUAD_ATTACK::Evaluate(void* data)
{
	return ReturnState(Attack(data));
}

std::string BT_ACTION_MUTALISK_SQUAD_ATTACK::GetDescription()
{
	return "BT_ACTION_MUTALISK_SQUAD_ATTACK";
}

BT_NODE::State BT_ACTION_MUTALISK_SQUAD_ATTACK::Attack(void* data)
{
	// first, align the squad with the target + ensure the squad is in range
	double squadFacingAngle = m_squad->getFacingAngle();

	BWAPI::Unit target = m_squad->getTarget();

	BWAPI::Position targetPosition = target->getPosition();
	BWAPI::Position squadPosition = m_squad->getPosition();

	double angleToTarget = atan2(targetPosition.y - squadPosition.y, targetPosition.x - squadPosition.x);

	if (fabs(squadFacingAngle - angleToTarget) > 0.1) {
		m_squad->moveTo(targetPosition);
		return BT_NODE::State::SUCCESS;
	}

	double targetDistance = squadPosition.getDistance(targetPosition);

	int mutaliskRange = BWAPI::UnitTypes::Zerg_Mutalisk.groundWeapon().maxRange();

	if (targetDistance > (double)mutaliskRange) {
		m_squad->moveTo(targetPosition);
		return BT_NODE::State::SUCCESS;
	}

	m_squad->attack(target);

	return BT_NODE::State::SUCCESS;
}




