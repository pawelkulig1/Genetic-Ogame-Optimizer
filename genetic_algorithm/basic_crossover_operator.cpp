#include "basic_crossover_operator.h"
#include <cstdint>

Chromosome BasicCrossoverOperator::cross(const Chromosome &parent1, const Chromosome &parent2)
{
	const int_fast8_t min_size = std::min(parent1.size(), parent2.size()) - 1;
	const int_fast8_t max_size = std::max(parent1.size(), parent2.size()) - 1;
	const int_fast8_t pivot1 = rand() % min_size;

	Chromosome child = Chromosome();
	child.reserve(max_size);
	child.set_chromosome(0, parent1.begin(), parent1.begin() + pivot1);
	child.set_chromosome(pivot1, parent2.begin()+pivot1, parent2.end());
	return child;
}
