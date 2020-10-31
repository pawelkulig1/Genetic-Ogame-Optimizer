//
// Created by Paweł Kulig on 2019-02-08.
//

#include <math.h>
#include "DeuteriumMine.h"

DeuteriumMine::DeuteriumMine(int planet_temperature,
		const Resources &defaultCost, 
		const double costRatio,
        const Resources &defaultProductionPerHour, 
		double productionRatio, 
		double energyRatio)
        : Mine(defaultCost, costRatio, defaultProductionPerHour, productionRatio, energyRatio) {
    name = "Deuterium Mine";
	m_planet_temperature = planet_temperature;
}

const Resources DeuteriumMine::getProductionPerHour() const
{
	return Resources(0, 0, 10 * lvl * cache_ratio[lvl] * ( 1.44 - 0.004 * m_planet_temperature), 0);
}
