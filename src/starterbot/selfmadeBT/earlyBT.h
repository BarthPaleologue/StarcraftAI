#pragma once

#include "BT.h"
#include "ZerglingUtils.h"
#include "Blackboard.h"
#include "Tools.h"

namespace BT_Builder 
{
    BT_NODE* terranEarlyMacroBT(Blackboard* _blackboard) {
        BT_PARALLEL_SEQUENCER* pBT = new BT_PARALLEL_SEQUENCER("EarlyGameVSTerran", nullptr, 10);
        
        //BT_DECO_CONDITION* pCheckIfAllIn = new BT_DECO_CONDITION("CheckIfAllIn", pBT, nullptr); //transfered elsewhere
            //BT_ACTION_UPDATE_BLACKBOARD<bool>* pToggleAllIn = new BT_ACTION_UPDATE_BLACKBOARD<bool>("ToggleAllIn", _blackboard->allIn, true, pCheckIfAllIn);

        BT_DECO_REPEATER* pRepeat = new BT_DECO_REPEATER("Repeat", pBT, 0, true, false, true);
        BT_SELECTOR* pBaseProductionMacro = new BT_SELECTOR("EarlyTerranBaseMacro", pRepeat, 3);
            
            BT_SELECTOR* pCheckIfCantWin = new BT_SELECTOR("CheckCantWin", pBaseProductionMacro, 5);
                BT_DECO_CONDITION_CANT_WIN* pCheckIfCantWinBrute = new BT_DECO_CONDITION_CANT_WIN("CheckIfCantWinBruteForce", pCheckIfCantWin);
                BT_CONDITION* decoToCond = new BT_CONDITION("dummy", pCheckIfCantWinBrute, [](void*) {return true; });

                BT_CONDITION* pCondAcademyTech = new BT_CONDITION("enemyHasAcademy", pCheckIfCantWin, 
                    [](void* _b) {Blackboard* data = (Blackboard*)_b; return data->EnemyHasBuilding(BWAPI::UnitTypes::Terran_Academy); });
                
                BT_CONDITION* pCondHasBunker = new BT_CONDITION("enemyHasBunker", pCheckIfCantWin,
                    [](void* _b) {Blackboard* data = (Blackboard*)_b; return data->EnemyHasBuilding(BWAPI::UnitTypes::Terran_Bunker); });

            BT_NODE* pZerglings = ZerglingUtils::TrainingTreeEarly(pBaseProductionMacro);

        BT_DECO_CONDITION* pCondBuildExtractor = new BT_DECO_CONDITION("CondBuildExtractor",pBT, 
            [](void*) {return Tools::CountUnitsOfType(BWAPI::UnitTypes::Zerg_Zergling, BWAPI::Broodwar->self()->getUnits()) >= 8; });
            BT_ACTION_BUILD* pActionBuildExtractor = new BT_ACTION_BUILD("ActionBuildExtractor", BWAPI::UnitTypes::Zerg_Extractor, NONE_POS, pCondBuildExtractor);

        BT_DECO_COND_GREATER_THAN<int>* pGasUsage = new BT_DECO_COND_GREATER_THAN<int>("EarlyTerranGasUsage", pBT, 90, _blackboard->currGas, false);
        //TODO: request upgrades "Metabolic Boost" (from spawning pool)
        BT_ACTION_BUILD* pUpgradeLair = new BT_ACTION_BUILD("UpgradeLair", BWAPI::UnitTypes::Zerg_Lair, NONE_POS, pGasUsage);
        
        return pBT;
    }

    BT_NODE* protossEarlyMacroBT(Blackboard* _blackboard) {
        BT_NODE* pBT = new BT_PARALLEL_SEQUENCER("EarlyGameVSProtoss", nullptr, 10);

        //BT_DECO_CONDITION* pCheckIfAllIn = new BT_DECO_CONDITION("CheckIfAllIn", pBT, nullptr); //transfered elsewhere
            //BT_ACTION_UPDATE_BLACKBOARD<bool>* pToggleAllIn = new BT_ACTION_UPDATE_BLACKBOARD<bool>("ToggleAllIn", _blackboard->allIn, true, pCheckIfAllIn);

        BT_DECO_REPEATER* pRepeat = new BT_DECO_REPEATER("Repeat", pBT, 0, true, false, true);
        BT_SELECTOR* pBaseProductionMacro = new BT_SELECTOR("EarlyProtossBaseMacro", pRepeat, 3);
            
            BT_DECO_CONDITION_CANT_WIN* pCheckIfReallyCantWin = new BT_DECO_CONDITION_CANT_WIN("CheckIfReallyCantWin", pBaseProductionMacro);
            // after that: station zerglings (check squad control) + request upgrade

            BT_NODE* pZerglings = ZerglingUtils::TrainingTreeEarly(pBaseProductionMacro);


        BT_DECO_CONDITION* pCondBuildExtractor = new BT_DECO_CONDITION("CondBuildExtractor", pBT,
            [](void*) {
                return Tools::CountUnitsOfType(BWAPI::UnitTypes::Zerg_Drone, BWAPI::Broodwar->self()->getUnits()) >= 12
                    && Tools::CountUnitsOfType(BWAPI::UnitTypes::Zerg_Hatchery, BWAPI::Broodwar->self()->getUnits()) >= 2;
            });
            BT_ACTION_BUILD* pActionBuildExtractor = new BT_ACTION_BUILD("ActionBuildExtractor", BWAPI::UnitTypes::Zerg_Extractor, NONE_POS, pCondBuildExtractor);

        BT_DECO_COND_GREATER_THAN<int>* pGasUsage = new BT_DECO_COND_GREATER_THAN<int>("EarlyProtossGasUsage", pBT, 90, _blackboard->currGas, false);
        BT_ACTION_BUILD* pUpgradeLair = new BT_ACTION_BUILD("UpgradeLair", BWAPI::UnitTypes::Zerg_Lair, NONE_POS, pGasUsage);

        return pBT;
    }
}