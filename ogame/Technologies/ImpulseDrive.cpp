#include "ImpulseDrive.h"
#include "common_includes.h"

ImpulseDrive::ImpulseDrive(Resources default_cost): Technology(default_cost)
{
	name = "Impulse Drive";
	m_requirements.push_back(std::make_pair(static_cast<int>(globals::Upgradables::LABORATORY), 2));
	m_requirements.push_back(std::make_pair(static_cast<int>(globals::Upgradables::ENERGY_TECHNOLOGY), 1));
}



