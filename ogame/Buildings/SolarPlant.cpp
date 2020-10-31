//
// Created by Paweł Kulig on 2019-02-08.
//

#include <cmath>
#include "SolarPlant.h"

Resources SolarPlant::getProductionPerHour() const {
    return Resources(0, 0, 0, productionRatio * lvl * cache_ratio[lvl]);
}

SolarPlant::SolarPlant(Resources defaultCost, double costRatio, int productionRatio) : Building(
        defaultCost, costRatio), productionRatio(productionRatio) {
    lvl = 0;
    name = "Solar Plant";
}


