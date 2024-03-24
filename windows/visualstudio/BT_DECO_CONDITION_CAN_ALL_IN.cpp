#include "BT_DECO_CONDITION_CAN_ALL_IN.h"

#include "ForceTools.h"


std::string BT_DECO_CONDITION_CAN_ALL_IN::GetDescription()
{
	return "BT_DECO_CONDITION_UNIT_IDLE";
}

bool BT_DECO_CONDITION_CAN_ALL_IN::canALlIn(void* data)
{
	BWAPI::Player enemy = BWAPI::Broodwar->enemy();
	BWAPI::Player me = BWAPI::Broodwar->self();

	BWAPI::UnitType myWorker =me->getRace().getWorker();
	BWAPI::UnitType enemyWorker =enemy->getRace().getWorker();


	//compute my score : 
	float myDPS=0;
	float enemyDPS=0;
	

	for (auto& unit : me->getUnits()){
		float dps = ForceTools::unitDPS(unit.getType(),me,enemyWorker,enemy);;
		if(dps>0){
			myDPS+=dps;
			myHp+=unit.getType().maxHitPoints();
		}
	}
	myDPS=myDPS/enemyWorker.maxHitPoints();
	float myScore = myDPS * pow(myHp, 1.5);



	//compute enemy score : 
	for (auto& unit : enemy->getUnits()){
		float dps = ForceTools::unitDPS(unit.getType(),enemy,myWorker,me);
		if(dps>0){
			enemyDPS+=dps;
			enemyHp+=unit.getType().maxHitPoints();
		}
	}
	float myHp=0;
	float enemyHp=0;

	enemyDPSDPS=enemyDPS/myWorker.maxHitPoints();
	float enemyScore = enemyDPS * pow(enemyHp, 1.5);
	
	if(enemyScore>myScore) return false;
	
	float remainingPercent = pow(1 - (enemyScore / myScore), (1 / (1.5)))
	if(remainingPercent>0.25) return true;
	return false;

}


