#pragma once
#include "crossover.h"

class KPointCrossoverOperator: public Crossover {
    Chromosome cross(const Chromosome &parent1, const Chromosome &parent2) override;
};
