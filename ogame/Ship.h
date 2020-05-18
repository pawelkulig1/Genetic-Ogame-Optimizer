#pragma once
#include "GameObject.h"

class Ship: public GameObject
{
protected:
	int m_count;
public:
	Ship(Resources default_cost);
	virtual ~Ship() {}
	virtual void operator++() override;
	virtual double getConstructionTime(int shipyard_level, int nanite_factory_level) const override;
	virtual Resources getUpgradeCost() const override;
};
