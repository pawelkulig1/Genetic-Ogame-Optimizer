#pragma once

#include "Building.h"

class FusionPlant: public Building 
{
	int m_production_ratio;
public:
	FusionPlant(Resources default_cost = Resources(900, 360, 180, 0.0), 
			double cost_ratio = 1.8, 
			double productionRatio = 30);
	virtual ~FusionPlant() {}

	Resources getProductionPerHour(int energetic_technology_lvl) const;
};
