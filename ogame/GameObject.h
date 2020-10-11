#pragma once
#include "Resources.h"
#include "common_includes.h"
#include <list>

class GameObject 
{
public:
	using Requirements = std::pair<int, int>;
protected:
	Resources defaultCost;
	std::string name;
	std::list<Requirements> m_requirements;
	globals::QueueIndex queue_index;
public:
	GameObject(Resources default_cost);
	virtual ~GameObject() {}
    virtual const Resources &getDefaultCost() const;
    virtual void operator++() = 0;
    virtual double getConstructionTime(int robot_factory_shipyard_level, int nanite_factory_level) const = 0;
    virtual Resources getUpgradeCost() const = 0;
	std::list<Requirements> get_requirements();
	void setName(std::string name);
	std::string getName() const;
	globals::QueueIndex getQueueIndex() const;
    friend std::ostream &operator<<(std::ostream &out, const GameObject &b);
};
