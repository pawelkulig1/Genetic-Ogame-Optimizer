#pragma once
#include "Technology.h"

class EspionageTechnology: public Technology {
public:
	EspionageTechnology(Resources default_cost = Resources(200, 1000, 200, 0));
	virtual ~EspionageTechnology() {}
};
