#pragma once

#include "BT.h"
#include "ZerglingUtils.h"
#include "OverlordUtils.h"
#include "MutaliskUtils.h"
#include "UpgradeBT.h"

namespace BT_Builder
{
	BT_NODE* buildMainBT(Blackboard *blackboard) {
        BT_NODE* pBT = new BT_DECORATOR("EntryPoint", nullptr);

        BT_PARALLEL_SEQUENCER* pMainParallelSeq = new BT_PARALLEL_SEQUENCER("MainParallelSequence", pBT, 10);

        // upgrade manager
        BT_Builder::buildUpgradeBT(pMainParallelSeq);

        //Farming Minerals forever
        BT_DECO_REPEATER* pFarmingMineralsForeverRepeater = new BT_DECO_REPEATER("RepeatForeverFarmingMinerals", pMainParallelSeq, 0, true, false, true);
        BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS* pSendWorkerToMinerals = new BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS("SendWorkerToMinerals", pFarmingMineralsForeverRepeater);

        // ---------------------- HQ (Hatchery, Lair, Hive) management ---------------------

        // actually modifiable into a larva management
        BT_DECO_REPEATER* pHQActionRepeater = new BT_DECO_REPEATER("RepeatForeverHQAction", pMainParallelSeq, 0, true, false, true);
        BT_SELECTOR* selectHQAction = new BT_SELECTOR("SelectHQAction", pHQActionRepeater, 10);

        // check if not sparing minerals for tasks already required from elsewhere
        BT_DECO_INVERTER* pDecoMineralsRequiredElsewhere = new BT_DECO_INVERTER("DecoMineralsRequiredElsewhere", selectHQAction);
        BT_COND_NOTHING_REQUESTED* pNothingElseRequested = new BT_COND_NOTHING_REQUESTED("CondNothingElseRequested", pDecoMineralsRequiredElsewhere);

        // Build Natural Base
        // make sure scout before that
        //BT_ACTION_BUILD* pBuildNaturalBase = new BT_ACTION_BUILD("BuildNaturalBase", BWAPI::UnitTypes::Zerg_Hatchery, pData->naturalTilePosition,selectHQAction);

        //Build Additional overlords
        OverlordUtils::CreateTrainingTree(selectHQAction);

        //Training Workers
        //BT_DECO_CONDITION* pNotAllIn = new BT_DECO_CONDITION("NotAllIn", selectHQAction, []()); // maybe a condition "read blackboard"?
        BT_DECO_CONDITION_NOT_ENOUGH_WORKERS* pNotEnoughWorkers = new BT_DECO_CONDITION_NOT_ENOUGH_WORKERS("NotEnoughWorkers", selectHQAction); //pNotAllIn);
        BT_ACTION_TRAIN_UNIT* pTrainWorker = new BT_ACTION_TRAIN_UNIT("TrainWorker", BWAPI::UnitTypes::Zerg_Drone, false, pNotEnoughWorkers);

        // ---------------------- End of HQ management ---------------------

        return pBT;
	}
}