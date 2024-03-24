#pragma once

#include "BT.h"
#include "ZerglingUtils.h"
#include "Blackboard.h"

namespace BT_Builder 
{
    BT_NODE* terranEarlyMacroBT(Blackboard* _blackboard) {
        BT_PARALLEL_SEQUENCER* pBT = new BT_PARALLEL_SEQUENCER("EarlyGameVSTerran", nullptr, 10);
        
        //BT_DECO_CONDITION* pCheckIfAllIn = new BT_DECO_CONDITION("CheckIfAllIn", pBT, nullptr); //TODO
            //BT_ACTION_UPDATE_BLACKBOARD<bool>* pToggleAllIn = new BT_ACTION_UPDATE_BLACKBOARD<bool>("ToggleAllIn", _blackboard->allIn, true, pCheckIfAllIn);

        BT_SELECTOR* pBaseProductionMacro = new BT_SELECTOR("EarlyTerranBaseMacro", pBT, 3);
            
            BT_DECO_CONDITION_CANT_WIN* pCheckIfCantWin = new BT_DECO_CONDITION_CANT_WIN("CheckIfCantWin", pBaseProductionMacro);
            // bc there are a lot of conditions it may be better to have a selector (-> repeater) and then conditions
            // if enemy has academy tech
            // or enemy has built bunker
            // or just can't win with raw force
            // after that: station zerglings (check squad control) + request upgrade  

            BT_NODE* pZerglings = ZerglingUtils::TrainingTreeEarly(pBaseProductionMacro);

        BT_DECO_CONDITION* pCondBuildExtractor = new BT_DECO_CONDITION("CondBuildExtractor",pBT, nullptr); //TODO: "if more than 8 zerglings"
            BT_ACTION_BUILD* pActionBuildExtractor = new BT_ACTION_BUILD("ActionBuildExtractor", BWAPI::UnitTypes::Zerg_Extractor, NONE_POS, pCondBuildExtractor);

        BT_DECO_COND_GREATER_THAN<int>* pGasUsage = new BT_DECO_COND_GREATER_THAN<int>("EarlyTerranGasUsage", pBT, 90, _blackboard->currGas, false);
        
        //TODO: request upgrades "Metabolic Boost" (from spawning pool) then lair (see miro)
        
        return pBT;
    }

    BT_NODE* protossEarlyMacroBT(Blackboard* _blackboard) {
        BT_NODE* pBT = new BT_PARALLEL_SEQUENCER("EarlyGameVSProtoss", nullptr, 10);

        //BT_DECO_CONDITION* pCheckIfAllIn = new BT_DECO_CONDITION("CheckIfAllIn", pBT, nullptr); //TODO
            //BT_ACTION_UPDATE_BLACKBOARD<bool>* pToggleAllIn = new BT_ACTION_UPDATE_BLACKBOARD<bool>("ToggleAllIn", _blackboard->allIn, true, pCheckIfAllIn);

        BT_SELECTOR* pBaseProductionMacro = new BT_SELECTOR("EarlyProtossBaseMacro", pBT, 3);

            BT_DECO_CONDITION* pCheckIfReallyCantWin = new BT_DECO_CONDITION("CheckIfReallyCantWin", pBaseProductionMacro, nullptr); //TODO
            // after that: station zerglings (check squad control) + request upgrade

            
            BT_NODE* pZerglings = ZerglingUtils::TrainingTreeEarly(pBaseProductionMacro);


        BT_DECO_CONDITION* pCondBuildExtractor = new BT_DECO_CONDITION("CondBuildExtractor", pBT, nullptr); // TODO: after 2nd base is up and not done yet and 12 drones
            BT_ACTION_BUILD* pActionBuildExtractor = new BT_ACTION_BUILD("ActionBuildExtractor", BWAPI::UnitTypes::Zerg_Extractor, NONE_POS, pCondBuildExtractor);

        BT_DECO_COND_GREATER_THAN<int>* pGasUsage = new BT_DECO_COND_GREATER_THAN<int>("EarlyProtossGasUsage", pBT, 90, _blackboard->currGas, false);
        BT_ACTION_BUILD* pUpgradeLair = new BT_ACTION_BUILD("UpgradeLair", BWAPI::UnitTypes::Zerg_Lair, NONE_POS, pGasUsage);

        return pBT;
    }
}