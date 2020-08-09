#include "PMX_crossover_operator.h"
#include "random_generators.h"
#include <map>
#include <iostream>

Chromosome PMXCrossoverOperator::cross(const Chromosome &parent1, const Chromosome &parent2)
{
    const int_fast32_t min_size = std::min(parent1.size(), parent2.size()) - 1;

    Chromosome child = Chromosome();
	child.reserve(min_size);
	if (min_size <= 3)
		return parent1;
    RandomGenerators *rnd = RandomGenerators::get_instance();
	const int_fast32_t p1 = rnd->get_random_int(0, min_size-3);
	const int_fast32_t p2 = rnd->get_random_int(p1+1, min_size-1);
	
	//create mapping:
	//std::map<Chromosome::chromosome_type, Chromosome::chromosome_type> mapping;
	//for(int i=p1;i<=p2;i++)
	//{
	//	mapping.insert(std::pair<int, int>(i, parent2.get(i)));
	//}

    for (int i=0;i<=min_size;i++)
    {
		if (i >= p1 && i <= p2)
		{
			child.append_gene(parent1.get(i));
			continue;
		}
		
		Chromosome::chromosome_type val = parent2.get(i);
		//auto found = mapping.find(val);
		//while( found != mapping.end() && found->second != val)
	//	{
	//		val = found->second;
	//		found = mapping.find(val);
	//	}
		child.append_gene(val);
    }
    return child;
}

