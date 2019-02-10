//
// Created by Paweł Kulig on 2019-02-08.
//

#include "CrystalMine.h"

CrystalMine::CrystalMine(const Resources &defaultCost, const double costRatio,
                         const Resources &defaultProductionPerHour, double productionRatio, double energyRatio) : Mine(
        defaultCost, costRatio, defaultProductionPerHour, productionRatio, energyRatio) {
    lvl = 0;
    name = "Crystal Mine";
}



