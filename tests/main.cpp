#include <iostream>
#include "basic_crossover_operator.h"
#include "chromosome.h"

extern bool test_mines_cost();
extern bool test_upgrade_time();
extern bool test_basic_crossover();
//extern bool test_generate_initial_population();
extern bool test_upgrade();
extern bool test_queues();
extern bool test_my_queue();

int main()
{
	
	srand(time(NULL));
	//test_mines_cost();
	//test_upgrade_time();
	//test_basic_crossover();
	// test_upgrade();
	// test_queues();
	test_my_queue();
}
