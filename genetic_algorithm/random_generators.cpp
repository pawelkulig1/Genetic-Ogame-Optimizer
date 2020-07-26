#include "random_generators.h"
#include <stdexcept>

RandomGenerators *RandomGenerators::m_random_generators = nullptr;

RandomGenerators::RandomGenerators() 
{
	mt = std::mt19937(rd());
}

RandomGenerators *RandomGenerators::get_instance()
{
	if (m_random_generators == nullptr)
	{
		m_random_generators = new RandomGenerators;
	}
	return m_random_generators;
}

double RandomGenerators::get_random_double(double min, double max)
{
	std::uniform_real_distribution<double> dist(min, max);
	return dist(mt);
}

int RandomGenerators::get_random_int(int min, int max)
{
	if (max <= min){
		throw(std::runtime_error("get_random_int max <= min"));
	}
	std::uniform_int_distribution<int> dist(min, max);
	return dist(mt);
}
