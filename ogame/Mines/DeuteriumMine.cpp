//
// Created by Paweł Kulig on 2019-02-08.
//

#include <math.h>
#include "DeuteriumMine.h"


//Resources DeuteriumMine::getProductionPerHour() {
//    return Resources(0, 0, productionRatio * lvl * pow(1.1, lvl) * (1.44 - 0.004 * planet_temperature), 0);
//}

DeuteriumMine::DeuteriumMine(int planet_temperature,
		const Resources &defaultCost, 
		const double costRatio,
        const Resources &defaultProductionPerHour, 
		double productionRatio, 
		double energyRatio)
        : Mine(defaultCost, costRatio, defaultProductionPerHour, productionRatio, energyRatio) {
    name = "Deuterium Mine";
}

const Resources DeuteriumMine::getProductionPerHour() const
{
	return Resources(0, 0, 10 * lvl * pow(1.1, lvl ) * ( 1.44 - 0.004 * planet_temperature), 0);
}
