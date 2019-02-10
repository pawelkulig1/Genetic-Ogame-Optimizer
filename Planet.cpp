//
// Created by Paweł Kulig on 2019-02-08.
//

#include "Planet.h"
#include <cmath>

Planet::Planet() : metalMine(MetalMine()),
                   crystalMine(CrystalMine()),
                   deuteriumMine(DeuteriumMine()),
                   solarPlant(SolarPlant()),
                   resources(Resources(500, 500, 0, 0)),
                   productionFactor(1) {}

void Planet::passTime(double seconds) {
    resources = resources + (getPlanetExtraction() / 3600) * seconds;
}

bool Planet::upgradeBuilding(Building &building) {
    Resources upgradeCost = building.getNextLevelCost();
    if (resources >= upgradeCost) {

        resources = resources - upgradeCost;

        //add resources loaded during building time
        resources = resources + (getPlanetExtraction() / 3600) * building.getConstructionTime();

        building.operator++();
        resources.setEnergy(calculatePlanetEnergy());

        //calculate production factor

        productionFactor = (
                solarPlant.getProductionPerHour().at(3) /
                (
                        metalMine.getEnergyConsumption().at(3) +
                        crystalMine.getEnergyConsumption().at(3) +
                        deuteriumMine.getEnergyConsumption().at(3)
                )
        );

        if (metalMine.getEnergyConsumption().at(3) +
            crystalMine.getEnergyConsumption().at(3) +
            deuteriumMine.getEnergyConsumption().at(3) == 0)
            productionFactor = 0;

        if (productionFactor > 1)
            productionFactor = 1;

        return true;
    }
    return false;
}

double Planet::getProductionFactor() const {
    return productionFactor;
}

double Planet::getTimeToBuild(Building const &b) {
    double maxDiff = 0;
    Resources costDelta;
    Resources extraction = getPlanetExtraction();
    costDelta = resources - b.getNextLevelCost();
    if (abs(costDelta.at(0)) > maxDiff)
        return abs(costDelta.at(0)) / extraction.at(0) * 3600;
    if (abs(costDelta.at(1)) > maxDiff)
        return abs(costDelta.at(1)) / extraction.at(1) * 3600;
    if (abs(costDelta.at(2)) > maxDiff)
        return abs(costDelta.at(2)) / extraction.at(2) * 3600;
    return 0;
}

Resources Planet::getPlanetExtraction() {
    Resources retResources = Resources(
            (metalMine.getProductionPerHour() * productionFactor + metalMine.getDefaultProductionPerHour()).at(0),
            (crystalMine.getProductionPerHour() * productionFactor + crystalMine.getDefaultProductionPerHour()).at(1),
            (deuteriumMine.getProductionPerHour() * productionFactor + deuteriumMine.getDefaultProductionPerHour()).at(
                    2),
            calculatePlanetEnergy());

    return retResources;
}

MetalMine &Planet::getMetalMine() {
    return metalMine;
}

CrystalMine &Planet::getCrystalMine() {
    return crystalMine;
}

DeuteriumMine &Planet::getDeuteriumMine() {
    return deuteriumMine;
}

SolarPlant &Planet::getSolarPlant() {
    return solarPlant;
}

Resources &Planet::getResources() {
    return resources;
}

int Planet::calculatePlanetEnergy() {
    return (solarPlant.getProductionPerHour() - metalMine.getEnergyConsumption() -
            crystalMine.getEnergyConsumption() - deuteriumMine.getEnergyConsumption()).at(3);
}



