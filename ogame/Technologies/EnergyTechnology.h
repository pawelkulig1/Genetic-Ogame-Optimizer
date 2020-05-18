#pragma once
#include "Technology.h"

class EnergyTechnology: public Technology {
public:
	EnergyTechnology(Resources default_cost = Resources(0, 800, 400, 0));
	virtual ~EnergyTechnology() {}
};
