#pragma once

#include <vector>
#include <utility>

template <class T>
class Crossover
{
public:
	virtual std::pair<std::vector<T>, std::vector<T> > cross(const std::vector<T> &parent1, const std::vector<T> &parent2) = 0;
	virtual ~Crossover(){};
};
