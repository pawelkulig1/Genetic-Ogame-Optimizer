//
// Created by Paweł Kulig on 2019-02-07.
//

#include "MetalMine.h"

MetalMine::MetalMine(const Resources &defaultCost, const double costRatio, const Resources &defaultProductionPerHour,
                     double productionRatio, double energyRatio) : Mine(defaultCost, costRatio,
                                                                        defaultProductionPerHour, productionRatio,
                                                                        energyRatio) {
    lvl = 0;
    name = "Metal Mine";
}

