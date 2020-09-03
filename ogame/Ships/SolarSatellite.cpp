#include "SolarSatellite.h"
#include "common_includes.h"


SolarSatellite::SolarSatellite(Resources default_cost): Ship(default_cost)
{
	name = "Solar Satellite";
	m_requirements.push_back(std::make_pair(static_cast<int>(globals::Upgradables::SHIPYARD), 1));
}

Resources SolarSatellite::getProductionPerHour(int planet_temperature) const 
{
	return Resources(0, 0, 0, ((planet_temperature + 160) / 6) * m_count);
}


