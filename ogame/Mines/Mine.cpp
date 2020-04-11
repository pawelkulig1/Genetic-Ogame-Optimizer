//
// Created by Paweł Kulig on 2019-01-12.
//

#include <cmath>
#include "Mine.h"

Resources Mine::getEnergyConsumption() const {
    return Resources(0, 0, 0, energyRatio * lvl * pow(1.1, lvl));
}

const Resources &Mine::getDefaultProductionPerHour() const {
    return defaultProductionPerHour;
}

Mine::Mine(const Resources &defaultCost, const double costRatio, const Resources &defaultProductionPerHour,
           double productionRatio, double energyRatio) : Building(defaultCost, costRatio),
                                                         defaultProductionPerHour(defaultProductionPerHour),
                                                         productionRatio(productionRatio), energyRatio(energyRatio) {}
