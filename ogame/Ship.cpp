#include "Ship.h"
#include <math.h>

Ship::Ship(Resources default_cost) : GameObject(default_cost)
{
	m_count = 0;
	queue_index = globals::QueueIndex::SHIP;
}

void Ship::operator++() 
{
	m_count += 1;
}

double Ship::getConstructionTime(int shipyard_level, int nanite_factory_level) const
{
    return (3600 * (defaultCost.at(0) + defaultCost.at(1)) / (2500 * (shipyard_level + 1)) * pow(0.5, nanite_factory_level));
}

Resources Ship::getUpgradeCost() const 
{
	return defaultCost;
}
