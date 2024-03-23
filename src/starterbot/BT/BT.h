#pragma once
//#define BT_DEBUG_VERBOSE
 
#include "BT_NODE.h"
#include "BT_LEAF.h"
#include "BT_ACTION.h"
#include "BT_DECORATOR.h"

//Composite notes
#include "BT_SEQUENCER.h"
#include "BT_SELECTOR.h"
#include "BT_PARALLEL_SEQUENCER.h"
#include "BT_PARALLEL_SELECTOR.h"

//Decorators
#include "BT_DECO_CONDITION.h"
#include "BT_DECO_COND_GREATER_THAN.h"
#include "BT_DECO_COND_LESSER_THAN.h"

#include "BT_DECO_INVERTER.h"
#include "BT_DECO_REPEATER.h"
#include "BT_DECO_RETURN_FAILURE.h"
#include "BT_DECO_RETURN_SUCCESS.h"
#include "BT_DECO_UNTIL_FAILURE.h"
#include "BT_DECO_UNTIL_SUCCESS.h"

// Conditions
#include "BT_CONDITION.h"
#include "BT_COND_GREATER_THAN.h"
#include "BT_COND_LESSER_THAN.h"
#include "BT_COND_NOTHING_REQUESTED.h"
#include "BT_COND_VISIBLE.h"
#include "BT_COND_EXPLORED.h"
#include "BT_UNIT_CONDITION.h"
#include "BT_SQUAD_CONDITION.h"

///Decorator Conditions
#include "BT_DECO_UNIT_CONDITION.h"
#include "BT_DECO_CONDITION_NOT_ENOUGH_WORKERS.h"
#include "BT_DECO_CONDITION_NOT_ENOUGH_UNIT.h"
#include "BT_DECO_CONDITION_BUILD_ORDER_FINISHED.h"
#include "BT_DECO_CONDITION_UNIT_IDLE.h"
#include "BT_DECO_CONDITION_NOT_ENOUGH_OVERLORDS.h"
#include "BT_DECO_CONDITION_UNIT_QUORUM.h"

///Actions
#include "BT_ACTION_IDLE.h"
#include "BT_ACTION_WAIT.h"
#include "BT_ACTION_LOG.h"
#include "BT_ACTION_BUILD.h"

#include "BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS.h"
#include "BT_ACTION_BUILD_SUPPLY_PROVIDER.h"
#include "BT_ACTION_GO_TO_ENEMY_BASE.h"
#include "BT_ACTION_TRAIN_UNIT.h"
#include "BT_ACTION_MOVE_ALL_ZERGLINGS_TO_ENEMY_BASE.h"
#include "BT_ACTION_SMART_ATTACK.h"

#include "BT_ACTION_UPGRADE_ULTRALISK.h"
#include "BT_ACTION_UPGRADE_MUTALISK.h"
#include "BT_ACTION_UPGRADE_DEFILER.h"
