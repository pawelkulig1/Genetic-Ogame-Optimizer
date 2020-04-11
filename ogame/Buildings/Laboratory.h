#pragma once
#include "Building.h"

class Laboratory : public Building
{
public:
	Laboratory(
			Resources default_cost = Resources(200, 400, 200, 0.0), 
			double cost_ratio = 2);
	virtual ~Laboratory();
};
