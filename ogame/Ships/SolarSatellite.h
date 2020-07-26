#pragma once
#include "Ship.h"
#include "Resources.h"

class SolarSatellite: public Ship
{
public:
	SolarSatellite(Resources default_cost = Resources(0, 2e3, 500, 0));
	virtual ~SolarSatellite() {}
	Resources getProductionPerHour(int planet_temperature) const;
};
