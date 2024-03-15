#pragma once

namespace BT_Builder {
	BT_NODE* buildEarlyAllInBT() {
        BT_NODE* pBtAllIn = new BT_DECORATOR("EntryPoint", nullptr);

        BT_PARALLEL_SEQUENCER* pMainParallelSeqAllIn = new BT_PARALLEL_SEQUENCER("MainParallelSequenceAllIn", pBtAllIn, 10);

        //Farming Minerals forever
        BT_DECO_REPEATER* pFarmingMineralsForeverRepeaterAllIn = new BT_DECO_REPEATER("RepeatForeverFarmingMineralsAllIn", pMainParallelSeqAllIn, 0, true, false, true);
        BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS* pSendWorkerToMineralsAllIn = new BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS("SendWorkerToMineralsAllIn", pFarmingMineralsForeverRepeaterAllIn);

        // ---------------------- HQ (Hatchery, Lair, Hive) management ---------------------

        BT_DECO_REPEATER* pHQActionRepeaterAllIn = new BT_DECO_REPEATER("RepeatForeverHQActionAllIn", pMainParallelSeqAllIn, 0, true, false, true);
        BT_SELECTOR* selectHQActionAllIn = new BT_SELECTOR("SelectHQActionAllIn", pHQActionRepeaterAllIn, 10);

        //Build Additional overlords
        OverlordUtils::CreateTrainingTree(selectHQActionAllIn);

        // Handling build order finished
        ZerglingUtils::CreateTrainingTree(selectHQActionAllIn);

        return pBtAllIn;
	}
}