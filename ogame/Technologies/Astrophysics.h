#pragma once
#include "Technology.h"

class Astrophysics : public Technology
{
public:
	Astrophysics(Resources default_cost = Resources(4e3, 8e3, 4e3, 0), double cost_ratio = 1.75);
	virtual ~Astrophysics() {}
};
