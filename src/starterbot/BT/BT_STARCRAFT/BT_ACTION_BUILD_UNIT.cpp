#pragma once // this is important because the template header will include the cpp and the cpp will try to include the template again
#include "BT_ACTION_BUILD_UNIT.h"
#include "Tools.h"
#include "Blackboard.h"
#include <typeinfo>


template<BWAPI::UnitTypes::Enum::Enum T>
BT_ACTION_BUILD_UNIT<T>::BT_ACTION_BUILD_UNIT(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {
}

template<BWAPI::UnitTypes::Enum::Enum T>
BT_NODE::State BT_ACTION_BUILD_UNIT<T>::Evaluate(void* data)
{
    return ReturnState(BuildUnit(data));
}

template<BWAPI::UnitTypes::Enum::Enum T>
std::string BT_ACTION_BUILD_UNIT<T>::GetDescription()
{
    return "BUILD " + BT_ACTION_BUILD_UNIT::UnitTypeString;
}

template<BWAPI::UnitTypes::Enum::Enum T>
BT_NODE::State BT_ACTION_BUILD_UNIT<T>::BuildUnit(void* data)
{
    Blackboard* pData = (Blackboard*)data;

    const bool startedBuilding = Tools::BuildBuilding(T);

    if (startedBuilding)
        BWAPI::Broodwar->printf("Started Building %s", UnitTypeString);

    return startedBuilding ? BT_NODE::SUCCESS : BT_NODE::FAILURE;
}


template<BWAPI::UnitTypes::Enum::Enum T>
const std::string BT_ACTION_BUILD_UNIT<T>::UnitTypeString = typeid(T).name();
