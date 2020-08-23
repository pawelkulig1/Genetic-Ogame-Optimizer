#pragma once
#include "Ship.h"

class SmallCargo: public Ship
{
public:
	SmallCargo(Resources default_cost = Resources(2e3, 2e3, 0, 0));
	virtual ~SmallCargo() {}
};
