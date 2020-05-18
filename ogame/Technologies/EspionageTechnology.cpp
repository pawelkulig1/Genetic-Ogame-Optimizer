#include "EspionageTechnology.h"
#include "common_includes.h"

EspionageTechnology::EspionageTechnology(Resources default_cost): Technology(default_cost)
{
	name = "Espionage Technology";
	m_requirements.push_back(std::make_pair(globals::Upgradables::LABORATORY, 3));
}
