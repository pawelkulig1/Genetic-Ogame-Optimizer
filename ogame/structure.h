#pragma once
#include "Resources.h"
#include <list>

class Structure 
{
public:
	using Requirements = std::pair<int, int>;
protected:
	int lvl;
	const Resources defaultCost;
	const double costRatio;
	std::string name;
	std::list<Requirements> m_requirements;
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
	std::list<Requirements> get_requirements();
	void setName(std::string name);
	std::string getName() const;
    friend std::ostream &operator<<(std::ostream &out, const Structure &b);
};
