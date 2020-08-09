#include "k_point_crossover_operator.h"
#include "random_generators.h"

Chromosome KPointCrossoverOperator::cross(const Chromosome &parent1, const Chromosome &parent2)
{
    RandomGenerators *rnd = RandomGenerators::get_instance();
    const int_fast32_t min_size = std::min(parent1.size(), parent2.size()) - 1;

    Chromosome child = Chromosome();
	child.reserve(min_size);
    int i = 0;
    for (;i<min_size;i++)
    {
        if (rnd->get_random_int(0, 1) != 0)
            child.append_gene(parent2.get(i));
        else
        {
            child.append_gene(parent1.get(i));
        }
    }
    return child;
}
