#include "basic_crossover_operator.h"
#include "chromosome.h"

bool test_basic_crossover()
{
    BasicCrossoverOperator crossover = BasicCrossoverOperator();

	Chromosome parent1 = Chromosome();
	Chromosome parent2 = Chromosome();
	std::vector<Chromosome::chromosome_type> vec1 = {1,2,3,4,5};
	std::vector<Chromosome::chromosome_type> vec2 = {5,4,3,2,1};
	parent1.set_chromosome(vec1);
	parent2.set_chromosome(vec2);

	Chromosome child = crossover.cross(parent1, parent2);
	std::vector<Chromosome::chromosome_type> out_vec = {1,2,3,2,1}; 
	//assuming rand() gives always the same number

	for (int i=0;i<child.size();i++)
	{
		assert(child.get(i) == out_vec.at(i));
	}
	return true;
}
