#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>


template<BWAPI::UnitTypes::Enum::Enum T>
class BT_ACTION_BUILD_UNIT : public BT_ACTION
{
public:
    BT_ACTION_BUILD_UNIT(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State BuildUnit(void* data);

    static const std::string UnitTypeString;
};

// This is necessary as this is a template class
// see https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file for a detailled explanation
// see also https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl for more details
#include "BT_ACTION_BUILD_UNIT.cpp"