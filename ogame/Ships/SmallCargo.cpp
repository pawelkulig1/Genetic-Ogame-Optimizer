#include "SmallCargo.h"
#include "common_includes.h"

SmallCargo::SmallCargo(Resources default_cost): Ship(default_cost)
{
	name = "Small Cargo";
	m_requirements.push_back(std::make_pair(static_cast<int>(globals::Upgradables::SHIPYARD), 2));
	m_requirements.push_back(std::make_pair(static_cast<int>(globals::Upgradables::COMBUSTION_DRIVE), 2));
}
