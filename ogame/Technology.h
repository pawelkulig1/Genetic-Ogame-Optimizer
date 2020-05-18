#pragma once
#include "structure.h"

class Technology : public Structure 
{
public:	
	Technology(Resources default_cost, double cost_ratio = 2.0);
	virtual ~Technology() {}
    virtual double getConstructionTime(int labolatory_level, int not_important=0) const override;
};
