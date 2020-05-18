#pragma once
#include "Ship.h"

class SolarSatellite: public Ship
{
public:
	SolarSatellite(Resources default_cost = Resources(0, 2e3, 500, 0));
	virtual ~SolarSatellite() {}
	double getProductionPerHour(int planet_temperature) const;
};
