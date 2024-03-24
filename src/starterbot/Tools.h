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

    bool canAllIn();
    
    bool cantWin();



    BWAPI::Position getClosestDefenceRegion(BWAPI::Position pos, int myIdx);
    bool BuildCreepColony(BWAPI::Unit hatchery, int myIdx);
    bool BuildSunkenColony(BWAPI::Unit hatchery);
}