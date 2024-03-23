#pragma once

#include "MapTools.h"
#include "targeting/TargetingTools.h"
#include "BT.h"
#include <BWAPI.h>
#include "Blackboard.h"
//#include "map.h"

class StarterBot
{
private:
    MapTools m_mapTools;
	BT_NODE* pMainBT;
	BT_NODE* pEarlyMacroBT;
	BT_NODE* pMidMacroBT;
	BT_NODE* pLateMacroBT;

	//BT_NODE* pBtTest;
	Blackboard *pData;

	std::map<BWAPI::Unit, BT_NODE*> m_unitBT{};
	std::map<Squad*, BT_NODE*> m_mutaliskSquadsBT{};

public:

    StarterBot();

    // helper functions to get you started with bot programming and learn the API
    void drawDebugInformation();

    // functions that are triggered by various BWAPI events from main.cpp
	void onStart();
	void onFrame();
	void onEnd(bool isWinner);
	void onUnitDestroy(BWAPI::Unit unit);
	void onUnitMorph(BWAPI::Unit unit);
	void onSendText(std::string text);
	void onUnitCreate(BWAPI::Unit unit);
	void onUnitComplete(BWAPI::Unit unit);
	void onUnitShow(BWAPI::Unit unit);
	void onUnitHide(BWAPI::Unit unit);
	void onUnitRenegade(BWAPI::Unit unit);
	
	//functions for initialisation :
	void save_base_position();
	void create_minerals_table();

};