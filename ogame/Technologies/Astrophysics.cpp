#include "Astrophysics.h"
#include "common_includes.h"

Astrophysics::Astrophysics(Resources default_cost, double cost_ratio): Technology(default_cost, cost_ratio)
{
	name = "Astrophysics";
	m_requirements.push_back(std::make_pair(static_cast<int>(globals::Upgradables::ESPIONAGE_TECHNOLOGY), 4));
	m_requirements.push_back(std::make_pair(static_cast<int>(globals::Upgradables::IMPULSE_DRIVE), 3));
	m_requirements.push_back(std::make_pair(static_cast<int>(globals::Upgradables::LABORATORY), 3));
}
