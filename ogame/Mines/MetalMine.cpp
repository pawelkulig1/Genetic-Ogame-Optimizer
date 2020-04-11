//
// Created by Paweł Kulig on 2019-02-07.
//

#include "MetalMine.h"
#include <math.h>

MetalMine::MetalMine(const Resources &defaultCost,
	   			     const double costRatio, 
					 const Resources &defaultProductionPerHour,
                     int productionRatio, 
					 int energyRatio) : 
			Mine(defaultCost, 
				 costRatio,
                 defaultProductionPerHour, 
				 productionRatio,
                 energyRatio)
{
    name = "Metal Mine";
}

const Resources MetalMine::getProductionPerHour() const
{
	return Resources(productionRatio * lvl * pow(1.1, lvl), 0, 0, 0);
}

