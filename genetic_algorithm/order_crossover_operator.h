#pragma once

class OrderCrossoverOperator: public Crossover
{
public:
	Chromosome cross(const Chromosome &parent1, const Chromosome &parent2) override final;		
}
