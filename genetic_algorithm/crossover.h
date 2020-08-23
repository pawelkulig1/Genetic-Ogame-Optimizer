#pragma once

#include <vector>
// #include "chromosome.h"
template <class T>
class Crossover
{
public:
	virtual std::vector<T> cross(const std::vector<T> &parent1, const std::vector<T> &parent2) = 0;
	virtual ~Crossover(){};
};
