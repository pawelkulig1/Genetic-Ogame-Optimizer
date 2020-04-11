#pragma once

#include "Building.h"

class FusionPlant: public Building 
{
	int m_production_ratio;
	int m_enetgetic_technology_lvl;
public:
	FusionPlant(Resources default_cost = Resources(900, 360, 180, 0.0), 
			double cost_ratio = 1.8, 
			double productionRatio = 30,
			double energetic_technology_lvl = 0
			);
	virtual ~FusionPlant() {}

	Resources getProductionPerHour() const;
};
