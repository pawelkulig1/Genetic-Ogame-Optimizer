#include "Shipyard.h"
#include "common_includes.h"

Shipyard::Shipyard(Resources default_cost) : Building(default_cost)
{
	name = "Shipyard";
	m_requirements.push_back(std::make_pair(globals::Upgradables::ROBOT_FACTORY, 2));
}
