#include <iostream>
#include "basic_crossover_operator.h"
#include "chromosome.h"

extern bool test_mines_cost();
extern bool test_upgrade_time();
extern bool test_basic_crossover();
extern bool test_generate_initial_population();

int main()
{
	
	srand(time(NULL));
	test_mines_cost();
	test_upgrade_time();
	test_basic_crossover();
	test_generate_random_chromosome();

	

}
