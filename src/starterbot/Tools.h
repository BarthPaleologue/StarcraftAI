#pragma once

#include <BWAPI.h>

namespace Tools
{
    BWAPI::Unit GetClosestUnitTo(BWAPI::Position p, const BWAPI::Unitset& units);
    BWAPI::Unit GetClosestUnitTo(BWAPI::Unit unit, const BWAPI::Unitset& units);
    BWAPI::Unitset GetUnitsInRadius(BWAPI::Position p,float r, const BWAPI::Unitset& units);

    int CountUnitsOfType(BWAPI::UnitType type, const BWAPI::Unitset& units);

    BWAPI::Unit GetUnitById(int ID,BWAPI::Unitset set);
    BWAPI::Unit GetUnitOfType(BWAPI::UnitType type);
    void GetAllUnitsOfType(BWAPI::UnitType type, std::vector<BWAPI::Unit>& units);
    BWAPI::Unit GetDepot();
    BWAPI::Unit GetClosestUnitOfType(BWAPI::UnitType type, BWAPI::Position pos, float distance = 100000);
    BWAPI::Unit GetClosestUnitOfTypeBeingBuilt(BWAPI::UnitType type, BWAPI::Position position, float distance = 100000);

    bool BuildBuilding(BWAPI::UnitType type);
    bool BuildBuildingAtPosition(BWAPI::UnitType type, BWAPI::TilePosition position);

    void DrawUnitBoundingBoxes();
    void DrawUnitCommands();

    void SmartRightClick(BWAPI::Unit unit, BWAPI::Unit target);

    int GetUnusedSupply(bool inProgress = false);
    int GetTotalSupply(bool inProgress = false);

    void DrawUnitHealthBars();
    void DrawHealthBar(BWAPI::Unit unit, double ratio, BWAPI::Color color, int yOffset);
 
    bool IsMine(BWAPI::Unit unit);

    bool TrainBuilderAtBase(BWAPI::Unit base, int num);


    BWAPI::Position getClosestDefenceRegion(BWAPI::Position pos, int myIdx) {
        int minDist = INT_MAX;
        BWAPI::Position closestPos;
        for (int i = 0; i < 7; i++) {
            int dist = pos.getDistance(DEFENCE_POS[myIdx][i]);
            if (dist < minDist) {
                minDist = dist;
                closestPos = DEFENCE_POS[myIdx][i];
            }
        }
        return closestPos;
    }

    bool BuildCreepColony(BWAPI::Unit hatchery, int myIdx) {
        BWAPI::UnitType type = BWAPI::UnitTypes::Zerg_Creep_Colony;
        BWAPI::Position desiredPos = getClosestDefenceRegion(hatchery->getPosition(),myIdx);
        BWAPI::TilePosition buildPos = BWAPI::Broodwar->getBuildLocation(type, hatchery->getTilePosition(), 500, true);
        return hatchery->build(type, buildPos);
    }

    bool BuildSunkenColony(BWAPI::Unit hatchery) {
        int minDist = INT_MAX;
        BWAPI::Unit closestUnit;
        for (auto& unit : BWAPI::Broodwar->self()->getUnits()) {
            if (unit->getType() == BWAPI::UnitTypes::Zerg_Creep_Colony && unit->isCompleted()) {
                int dist = unit->getPosition().getDistance(hatchery->getPosition());
                if (dist < minDist) {
					minDist = dist;
					closestUnit = unit;
				}
            }
        }
        return closestUnit->morph(BWAPI::UnitTypes::Zerg_Sunken_Colony);
	}
}