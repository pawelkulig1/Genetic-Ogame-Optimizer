//
// Created by Paweł Kulig on 2019-02-08.
//

#ifndef OGAME_PLANET_H
#define OGAME_PLANET_H


#include "Mines/DeuteriumMine.h"
#include "SolarPlant.h"
#include "Mines/CrystalMine.h"
#include "Mines/MetalMine.h"

class Planet {
private:
    MetalMine metalMine;
    CrystalMine crystalMine;
    DeuteriumMine deuteriumMine;
    SolarPlant solarPlant;
    Resources resources;
    double productionFactor;

public:
    Planet();

    void passTime(double);

    bool upgradeBuilding(Building &building);

    Resources getPlanetExtraction();

    double getTimeToBuild(Building const &b);

    int calculatePlanetEnergy();

    MetalMine &getMetalMine();

    CrystalMine &getCrystalMine();

    DeuteriumMine &getDeuteriumMine();

    SolarPlant &getSolarPlant();

    Resources &getResources();

    double getProductionFactor() const;
};


#endif //OGAME_PLANET_H
