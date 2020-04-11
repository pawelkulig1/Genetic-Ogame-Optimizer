#pragma once
#include <random>

class RandomGenerators
{
	std::random_device rd;
	std::mt19937 mt;

	static RandomGenerators *m_random_generators;
	RandomGenerators();
public:
	static RandomGenerators *get_instance();
	double get_random_double(double min, double max);
	int get_random_int(int min, int max);
};
