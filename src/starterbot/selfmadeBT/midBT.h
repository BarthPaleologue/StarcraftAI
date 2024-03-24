#pragma once

#include "BT.h"
#include "ZerglingUtils.h"
#include "MutaliskUtils.h"
#include "Blackboard.h"

namespace BT_Builder
{
    BT_NODE* terranMidMacroBT(Blackboard* _blackboard) {
        BT_PARALLEL_SEQUENCER* pBT = new BT_PARALLEL_SEQUENCER("MidGameVSTerran", nullptr, 10);

        BT_DECO_CONDITION_NOT_ENOUGH_UNIT* pCheckIfSpire = new BT_DECO_CONDITION_NOT_ENOUGH_UNIT("CheckIfSpireBuilt", pBT, BWAPI::UnitTypes::Zerg_Spire);
        BT_ACTION_BUILD* pBuildSpire = new BT_ACTION_BUILD("BuildSpire", BWAPI::UnitTypes::Zerg_Spire, NONE_POS, pCheckIfSpire);

        BT_ACTION_TRAIN_UNIT* pTrainRecoUnit = new BT_ACTION_TRAIN_UNIT("TrainRecommendedUnit", _blackboard->focusedTrainingUnit, true, pBT);

        BT_DECO_CONDITION* pCheckIfAllIn = new BT_DECO_CONDITION_ALL_IN("CheckIfAllIn", pBT); 
        BT_ACTION_UPDATE_BLACKBOARD<bool>* pToggleAllIn = new BT_ACTION_UPDATE_BLACKBOARD<bool>("ToggleAllIn", _blackboard->allIn, true, pCheckIfAllIn);

        BT_SELECTOR* pBaseProductionMacro = new BT_SELECTOR("MidTerranBaseMacro", pBT, 3);

        BT_DECO_CONDITION* pCheckIfCantMuta = new BT_DECO_CONDITION("CheckIfCantMuta", pBaseProductionMacro, nullptr); //TODO
        // bc there are a lot of conditions it may be better to have a selector (-> repeater) and then conditions
        // if enemy has science facility
        // or too much anti-air (includes turrets)
            // (either way) update the required worker count to 2*mineral patch count
            // if can't muta bc they have a lot of goliath or wraith
                // go for hydralisk (needs Hydralisk_Den first)
            // else request Hive

        return pBT;
    }

    BT_NODE* protossMid(Blackboard* _blackboard) {
        BT_PARALLEL_SEQUENCER* pBT = new BT_PARALLEL_SEQUENCER("MidGameVSProtoss", nullptr, 10);

        BT_DECO_CONDITION_NOT_ENOUGH_UNIT* pCheckIfSpire = new BT_DECO_CONDITION_NOT_ENOUGH_UNIT("CheckIfSpireBuilt", pBT, BWAPI::UnitTypes::Zerg_Spire);
        BT_ACTION_BUILD* pBuildSpire = new BT_ACTION_BUILD("BuildSpire", BWAPI::UnitTypes::Zerg_Spire, NONE_POS, pCheckIfSpire);

        BT_ACTION_TRAIN_UNIT* pTrainRecoUnit = new BT_ACTION_TRAIN_UNIT("TrainRecommendedUnit", _blackboard->focusedTrainingUnit, true, pBT);

        BT_DECO_CONDITION* pCheckIfAllIn = new BT_DECO_CONDITION_ALL_IN("CheckIfAllIn", pBT);
        BT_ACTION_UPDATE_BLACKBOARD<bool>* pToggleAllIn = new BT_ACTION_UPDATE_BLACKBOARD<bool>("ToggleAllIn", _blackboard->allIn, true, pCheckIfAllIn);

        BT_SELECTOR* pBaseProductionMacro = new BT_SELECTOR("MidProtossBaseMacro", pBT, 3);

        BT_DECO_CONDITION* pCheckIfCantMuta = new BT_DECO_CONDITION("CheckIfCantMuta", pBaseProductionMacro, nullptr); //TODO
        // bc there are a lot of conditions it may be better to have a selector (-> repeater) and then conditions
        // if enemy has science facility
        // or too much anti-air (includes turrets)
            // (either way) update the required worker count to 2*mineral patch count
            // go for hydralisk (needs Hydralisk_Den first)


        return pBT;
    }
}