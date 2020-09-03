#include "FusionPlant.h"
#include <math.h>
#include <list>
#include "common_includes.h"


FusionPlant::FusionPlant(Resources default_cost,
						double cost_ratio, 
						double productionRatio):
	Building(default_cost, cost_ratio)
{
	name = "Fusion Plant";
	m_production_ratio = productionRatio;
	m_requirements.push_back(std::make_pair(static_cast<int>(globals::Upgradables::DEUTERIUM_MINE), 5));
}

Resources FusionPlant::getProductionPerHour(int energetic_technology_lvl) const
{
    return Resources(0, 0, 10 * lvl * pow(1.1, lvl), m_production_ratio * lvl * pow(1.05 + energetic_technology_lvl * 0.01, lvl));
}

