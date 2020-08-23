#pragma once
#include "Technology.h"

class CombustionDrive: public Technology
{
public:
	CombustionDrive(Resources default_cost = Resources(400, 0, 600));
	virtual ~CombustionDrive() {}
};
