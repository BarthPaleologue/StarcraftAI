#include "BT_ACTION_MUTALISK_SQUAD_HOLD_POSITION.h"

BT_ACTION_MUTALISK_SQUAD_HOLD_POSITION::BT_ACTION_MUTALISK_SQUAD_HOLD_POSITION(std::string name, Squad squad, BT_NODE* parent)
	: BT_ACTION(name, parent), m_squad(squad)
{
}

BT_NODE::State BT_ACTION_MUTALISK_SQUAD_HOLD_POSITION::Evaluate(void* data)
{
	return ReturnState(HoldPosition(data));
}

std::string BT_ACTION_MUTALISK_SQUAD_HOLD_POSITION::GetDescription()
{
	return "BT_ACTION_MUTALISK_SQUAD_HOLD_POSITION";
}

BT_NODE::State BT_ACTION_MUTALISK_SQUAD_HOLD_POSITION::HoldPosition(void* data)
{
	// first, align the squad with the target + ensure the squad is in range
	double squadFacingAngle = m_squad.getFacingAngle();

	BWAPI::Unit target = m_squad.getTarget();

	BWAPI::Position targetPosition = target->getPosition();
	BWAPI::Position squadPosition = m_squad.getPosition();

	double angleToTarget = atan2(targetPosition.y - squadPosition.y, targetPosition.x - squadPosition.x);

	if (fabs(squadFacingAngle - angleToTarget) > 0.1) {
		m_squad.moveTo(targetPosition);
		return BT_NODE::State::SUCCESS;
	}

	double targetDistance = squadPosition.getDistance(targetPosition);

	int mutaliskRange = BWAPI::UnitTypes::Zerg_Mutalisk.groundWeapon().maxRange();

	if (targetDistance > (double)mutaliskRange) {
		m_squad.moveTo(targetPosition);
		return BT_NODE::State::SUCCESS;
	}

	// if squad too close to target, move away
	if (targetDistance < (double)mutaliskRange / 2.0) {
		BWAPI::Position fleeVector = squadPosition - targetPosition;
		fleeVector = fleeVector / fleeVector.getLength() * (double)mutaliskRange;
		m_squad.moveTo(squadPosition + fleeVector);
		return BT_NODE::State::SUCCESS;
	}

	// then, hold position
	m_squad.holdPosition();

	return BT_NODE::State::SUCCESS;
}


