#include "Laboratory.h"

Laboratory::Laboratory(Resources default_cost, double cost_ratio):
	Building(default_cost, cost_ratio)
{
	name="Laboratory";
}

Laboratory::~Laboratory() {}
