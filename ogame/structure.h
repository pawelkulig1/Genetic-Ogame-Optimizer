#pragma once
#include "GameObject.h"

class Structure : public GameObject
{
protected:
	int lvl;
	double costRatio;
public:
	virtual ~Structure();
	Structure(const Resources &defaultCost, double costRatio = 2);
    virtual int getLvl() const;
	virtual Resources getUpgradeCost() const override;
    virtual const double getCostRatio() const;
    virtual void setLvl(int lvl);
    virtual double getConstructionTime(int robot_factory_level, int nanite_factory_level) const override;
	virtual void operator++() override;
};
