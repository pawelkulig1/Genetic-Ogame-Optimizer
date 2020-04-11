#pragma once
#include "Building.h"

class Shipyard: public Building
{
public:
	Shipyard(Resources default_cost = Resources(400, 200, 100, 0.0));
	virtual ~Shipyard() {}
};
