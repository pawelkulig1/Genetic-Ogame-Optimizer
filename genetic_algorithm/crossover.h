#pragma once

#include "chromosome.h"

class Crossover
{
protected:
	virtual Chromosome cross(const Chromosome &parent1, const Chromosome &parent2) =0;
};
