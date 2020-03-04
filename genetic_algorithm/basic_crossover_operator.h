#pragma once
#include "crossover.h"

class BasicCrossoverOperator : public Crossover
{
public:
	Chromosome cross(const Chromosome &parent1, const Chromosome &parent2) override final;
};
