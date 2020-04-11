#pragma once

#include "Building.h"

class RobotFactory: public Building
{
public:
	RobotFactory(Resources default_cost = Resources(400, 120, 200, 0.0));
	virtual ~RobotFactory() {}
};
