//
// Created by Paweł Kulig on 2019-02-08.
//

#include "CrystalMine.h"
#include <math.h>

CrystalMine::CrystalMine(const Resources &defaultCost, const double costRatio,
                         const Resources &defaultProductionPerHour, double productionRatio, double energyRatio) : Mine(
        defaultCost, costRatio, defaultProductionPerHour, productionRatio, energyRatio) {
    name = "Crystal Mine";
}

const Resources CrystalMine::getProductionPerHour() const
{
	return Resources(0, productionRatio * lvl * cache_ratio[lvl], 0, 0);
}


