#pragma once
#include "Resources.h"

class Structure 
{
protected:
	int lvl;
	const Resources defaultCost;
	const double costRatio;
	std::string name;
public:
	virtual ~Structure();
	Structure(const Resources &defaultCost, double constRatio = 2);

    virtual Resources getNextLevelCost() const;

    virtual int getLvl() const;

    virtual const Resources &getDefaultCost() const;

    virtual const double getCostRatio() const;

    virtual void setLvl(int lvl);

    virtual void operator++();

    double getConstructionTime(int robot_factory_level, int nanite_factory_level);

	void setName(std::string name);

	std::string getName() const;

    friend std::ostream &operator<<(std::ostream &out, const Structure &b);
		
};
