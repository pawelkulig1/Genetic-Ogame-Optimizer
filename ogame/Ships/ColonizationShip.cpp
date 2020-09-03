#include "ColonizationShip.h"
#include "common_includes.h"

ColonizationShip::ColonizationShip(Resources default_cost): Ship(default_cost)
{
	name = "Colonization Ship";
	m_requirements.push_back(std::make_pair(static_cast<int>(globals::Upgradables::SHIPYARD), 4));
	m_requirements.push_back(std::make_pair(static_cast<int>(globals::Upgradables::IMPULSE_DRIVE), 3));
}
