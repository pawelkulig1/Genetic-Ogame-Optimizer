#pragma once
#include <math.h>
#include <array>
#include <utility>
#include "Mine2.h"

class CrystalMine
{
public:
	static constexpr Resources default_cost = {48, 24, 0};
	static constexpr double cost_ratio = 1.6;
	static constexpr int production_ratio = 20;
	static constexpr double default_production = 20;
	static constexpr int energy_ratio = 10;
	static constexpr int max_level = 40;

	static constexpr std::array<type, max_level> production_cache = generate_production<max_level>(production_ratio);
	static constexpr std::array<type, max_level> energy_usage_cache = generate_production<max_level>(energy_ratio);
	static constexpr std::array<Resources, max_level> cost_cache = generate_costs<max_level>(default_cost, cost_ratio);
	
	consteval static type get_production(int lvl)
	{
		return production_cache[lvl];
	}

	consteval static type get_energy_consumption(int lvl)
	{
		return energy_usage_cache[lvl];
	}

	consteval static Resources get_cost(int lvl)
	{
		return cost_cache[lvl];
	}

	consteval static type get_construction_time(int lvl, int robot_factory_level, int nanite_factory_level)
	{
		return 3600 * (get_cost(lvl).m + get_cost(lvl).c) / (2500 * (robot_factory_level + 1) * pow(0.5, nanite_factory_level));
	}

	consteval static std::array<std::pair<int, int>, 0> get_requirements()
	{
		return std::array<std::pair<int, int>, 0> {};
	}
};
