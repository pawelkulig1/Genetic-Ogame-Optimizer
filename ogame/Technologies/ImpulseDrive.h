#pragma once
#include "Technology.h"

class ImpulseDrive: public Technology
{
public:
	ImpulseDrive(Resources default_cost = Resources(2e3, 4e3, 600));
	virtual ~ImpulseDrive() {}
};
