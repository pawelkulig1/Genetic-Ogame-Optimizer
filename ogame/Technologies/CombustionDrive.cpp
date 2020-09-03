#include "CombustionDrive.h"
#include "common_includes.h"

CombustionDrive::CombustionDrive(Resources default_cost): Technology(default_cost)
{
	name = "Combustion Drive";
	m_requirements.push_back(std::make_pair(static_cast<int>(globals::Upgradables::LABORATORY), 1));
	m_requirements.push_back(std::make_pair(static_cast<int>(globals::Upgradables::ENERGY_TECHNOLOGY), 1));
}



