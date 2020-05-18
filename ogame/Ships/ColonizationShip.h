#pragma once
#include "Ship.h"

class ColonizationShip: public Ship
{
public:
	ColonizationShip(Resources default_cost = Resources(1e4, 2e4, 1e4, 0));
	virtual ~ColonizationShip() {}
};
