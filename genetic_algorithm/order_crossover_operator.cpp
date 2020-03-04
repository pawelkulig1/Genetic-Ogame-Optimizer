#include "order_crossover_operator.h"
#include <stdexcept>

Chromosome OrderCrossoverOperator::cross(const Chromosome &parent1, const Chromosome &parent2)
{
	const int shorter_len = std::min(parent1.size(), parent2.size());
	const int pivot1 = rand() % (shorter_len - 2);
	const int pivot2 = (rand() % (shorter_len - pivot1)) + pivot1;

	Chromosome child = Chromosome();
	child.reserve(shorter_len);
	throw std::runtime_error("not implemented yet!");
	//child.insert_gene(

	//std::cout<<pivot1 << " " << pivot2 << std::endl;


		
}
