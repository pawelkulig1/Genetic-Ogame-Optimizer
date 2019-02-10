//
// Created by Paweł Kulig on 2019-02-08.
//

#include <cmath>
#include "DeuteriumMine.h"


Resources DeuteriumMine::getProductionPerHour() {
    return Resources(0, 0, productionRatio * lvl * pow(1.1, lvl) * (1.44 - 0.004 * planetTemperature), 0);
}

DeuteriumMine::DeuteriumMine(const Resources &defaultCost, const double costRatio,
                             const Resources &defaultProductionPerHour, double productionRatio, double energyRatio)
        : Mine(defaultCost, costRatio, defaultProductionPerHour, productionRatio, energyRatio) {
    lvl = 0;
    name = "Deuterium Mine";
}
