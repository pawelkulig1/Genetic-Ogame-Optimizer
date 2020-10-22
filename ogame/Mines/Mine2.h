#pragma once
#include <math.h>
#include <array>

using type = uint64_t;

struct Resources
{
	type m;
	type c;
	type d;
    type e;
    constexpr Resources(type m, type c, type d, type e) : m(m), c(c), d(d), e(e) {}
    constexpr Resources(std::initializer_list<type> c): m(*c.begin()), c(*std::next(c.begin())), d(*std::next(std::next(c.begin()))), e(*std::next(std::next(std::next(c.begin())))) {}
};

template <size_t size>
consteval std::array<type, size> generate_production(double production_ratio, int default_production = 0)
{
	std::array<type, size> out{0};
	for (int i{0};i<size;i++)
	{
		out[i] = floor(production_ratio * i * pow(1.1, i) + default_production);
	}
	return out;
}

template <size_t size>
consteval std::array<Resources, size> generate_costs(Resources default_cost, double cost_ratio)
{
	std::array<Resources, size> out{Resources(0, 0, 0, 0)};
	for (size_t i{0};i<size;i++)
	{
		double temp = pow(cost_ratio, i);
		out[i] = Resources(static_cast<type>(default_cost.m * temp), 
				  static_cast<type>(default_cost.c * temp), 
				  static_cast<type>(default_cost.d * temp), 0);
	}
	return out;
}

