#pragma once

#include "BT.h"
#include "ZerglingUtils.h"
#include "Blackboard.h"

namespace BT_Builder 
{
    BT_NODE* terranEarlyMacroBT(BT_NODE* _parent, Blackboard* _blackboard) { //_parent is likely null btw
        BT_PARALLEL_SEQUENCER* pBT = new BT_PARALLEL_SEQUENCER("EarlyGameVSTerran", _parent, 10);
        
        BT_DECO_CONDITION* pCheckIfAllIn = new BT_DECO_CONDITION("CheckIfAllIn", pBT, nullptr); //TODO
        BT_ACTION_UPDATE_BLACKBOARD<bool>* pToggleAllIn = new BT_ACTION_UPDATE_BLACKBOARD<bool>("ToggleAllIn", _blackboard->allIn, true, pCheckIfAllIn);

        BT_SELECTOR* pBaseProductionMacro = new BT_SELECTOR("EarlyTerranBaseMacro", pBT, 3);

        BT_DECO_CONDITION* pCheckIfCantWin = new BT_DECO_CONDITION("CheckIfCantWin", pBaseProductionMacro, nullptr); //TODO
        // bc there are a lot of conditions it may be better to have a selector (-> repeater) and then conditions
        // if enemy has academy tech
        // or enemy has built bunker
        // or just can't win with raw force
        // after that: station zerglings (check squad control) + request upgrade  

        BT_NODE* pZerglings = ZerglingUtils::TrainingTreeEarly(pBaseProductionMacro);

        BT_DECO_CONDITION* pCondBuildExtractor = new BT_DECO_CONDITION("CondBuildExtractor",pBT, nullptr); //TODO: "if more than 8 zerglings
        BT_ACTION_BUILD* pActionBuildExtractor = new BT_ACTION_BUILD("ActionBuildExtractor", BWAPI::UnitTypes::Zerg_Extractor, NONE_POS, pCondBuildExtractor);

        BT_DECO_CONDITION* pGasUsage = new BT_DECO_CONDITION("EarlyTerranGasUsage", pBT, nullptr); //TODO
        //TODO: request upgrades "Metabolic Boost" (from spawning pool) then lair (see miro)
        
        return pBT;
    }

    BT_NODE* protossEarlyMacroBT(BT_NODE* _parent, Blackboard* _blackboard) { //_parent is likely null btw
        BT_NODE* pBT = new BT_PARALLEL_SEQUENCER("EarlyGameVSProtoss", _parent, 10);

        BT_DECO_CONDITION* pCheckIfAllIn = new BT_DECO_CONDITION("CheckIfAllIn", pBT, nullptr); //TODO
        BT_ACTION_UPDATE_BLACKBOARD<bool>* pToggleAllIn = new BT_ACTION_UPDATE_BLACKBOARD<bool>("ToggleAllIn", _blackboard->allIn, true, pCheckIfAllIn);

        BT_SELECTOR* pBaseProductionMacro = new BT_SELECTOR("EarlyProtossBaseMacro", pBT, 3);

        BT_DECO_CONDITION* pCheckIfReallyCantWin = new BT_DECO_CONDITION("CheckIfReallyCantWin", pBaseProductionMacro, nullptr); //TODO
        // after that: station zerglings (check squad control) + request upgrade

        BT_DECO_CONDITION* pCheckIfEightCantWin = new BT_DECO_CONDITION("CheckIfCantWinWith8", pBaseProductionMacro, nullptr); //TODO
        // ajust accordingly to the game state: _blackboard->minRequiredUnitCount[BWAPI::UnitTypes::Zerg_Zergling] = 8 or 12 in there
        BT_NODE* pZerglings = ZerglingUtils::TrainingTreeEarly(pBaseProductionMacro);

        BT_DECO_CONDITION* pCondBuildExtractor = new BT_DECO_CONDITION("CondBuildExtractor", pBT, nullptr); // TODO: after 2nd base is up and not done yet and 12 drones
        BT_ACTION_BUILD* pActionBuildExtractor = new BT_ACTION_BUILD("ActionBuildExtractor", BWAPI::UnitTypes::Zerg_Extractor, NONE_POS, pCondBuildExtractor);

        BT_DECO_CONDITION* pGasUsage = new BT_DECO_CONDITION("EarlyProtossGasUsage", pBT, nullptr); //TODO
        //TODO: request lair


        return pBT;
    }
}