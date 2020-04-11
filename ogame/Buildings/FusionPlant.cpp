#include "FusionPlant.h"
#include <math.h>
#include <list>
#include "common_includes.h"


FusionPlant::FusionPlant(Resources default_cost,
						double cost_ratio, 
						double productionRatio,
						double energetic_technology_lvl):
	Building(default_cost, cost_ratio)
{
	name = "Fusion Plant";
	m_production_ratio = productionRatio;
	m_enetgetic_technology_lvl = energetic_technology_lvl;
	m_requirements.push_back(std::make_pair(globals::Upgradables::DEUTERIUM_MINE, 5));
}

Resources FusionPlant::getProductionPerHour() const
{
    return Resources(0, 0, 10 * lvl * pow(1.1, lvl), m_production_ratio * lvl * pow(1.05 + m_enetgetic_technology_lvl * 0.01, lvl));
}
