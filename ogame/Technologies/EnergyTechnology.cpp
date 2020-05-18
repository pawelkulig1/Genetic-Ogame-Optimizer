#include "EnergyTechnology.h"
#include "common_includes.h"

EnergyTechnology::EnergyTechnology(Resources default_cost): Technology(default_cost)
{
	name = "Energy Technology";
	m_requirements.push_back(std::make_pair(globals::Upgradables::LABORATORY, 1));
}
