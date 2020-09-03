#include "basic_crossover_operator.h"
// #include "PMX_crossover_operator.h"
// #include "chromosome.h"
#include "utility.h"
#include <iostream>
#include <cassert>

// bool test_basic_crossover()
// {
//     BasicCrossoverOperator crossover = BasicCrossoverOperator();

// 	Chromosome parent1 = Chromosome();
// 	Chromosome parent2 = Chromosome();
// 	std::vector<Chromosome::chromosome_type> vec1 = {1,2,3,4,5};
// 	std::vector<Chromosome::chromosome_type> vec2 = {5,4,3,2,1};
// 	parent1.set_chromosome(vec1);
// 	parent2.set_chromosome(vec2);

// 	Chromosome child = crossover.cross(parent1, parent2);
// 	std::vector<Chromosome::chromosome_type> out_vec = {1,2,3,2,1}; 
// 	//assuming rand() gives always the same number

// 	for (int i=0;i<child.size();i++)
// 	{
// 		assert(child.get(i) == out_vec.at(i));
// 	}
// 	return true;
// }

// void test_PMX_crossover()
// {
//     PMXCrossoverOperator crossover = PMXCrossoverOperator();
// 	Chromosome parent1 = Chromosome();
// 	Chromosome parent2 = Chromosome();
// 	std::vector<Chromosome::chromosome_type> vec1 = {1,2,3,4,5};
// 	std::vector<Chromosome::chromosome_type> vec2 = {5,4,3,2,1};
// 	parent1.set_chromosome(vec1);
// 	parent2.set_chromosome(vec2);

// 	Chromosome child = crossover.cross(parent1, parent2);
// 	std::cout << child << std::endl;
// }


void run_genetic()
{
	//test_basic_crossover();
	// test_PMX_crossover();
}
