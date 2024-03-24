#include "BT_ACTION_SQUAD_SPREAD.h"

BT_ACTION_SQUAD_SPREAD::BT_ACTION_SQUAD_SPREAD(std::string name, Squad* squad, BT_NODE* parent)
	:BT_ACTION(name, parent)
{
}

BT_NODE::State BT_ACTION_SQUAD_SPREAD::Evaluate(void* data)
{
	return ReturnState(Spread(data));
}

std::string BT_ACTION_SQUAD_SPREAD::GetDescription()
{
	return "BT_ACTION_SQUAD_SPREAD";
}

BT_NODE::State BT_ACTION_SQUAD_SPREAD::Spread(void* data)
{
	BWAPI::Position squadCenter = m_squad->getPosition();

	for (auto unit : m_squad->getUnits()) {
		BWAPI::Position relativePosition = unit->getPosition() - squadCenter;
		double distanceToCenter = relativePosition.getLength();

		unit->move(squadCenter + relativePosition + relativePosition / distanceToCenter);
	}

	return BT_NODE::SUCCESS;
}


