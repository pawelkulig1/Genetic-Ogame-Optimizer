#include <iostream>
#include "basic_crossover_operator.h"
#include "chromosome.h"

extern bool test_mines_cost();
extern bool test_upgrade_time();
extern bool test_basic_crossover();
//extern bool test_generate_initial_population();
extern void run_ogame();
extern void run_genetic();

int main()
{
	
	// srand(time(NULL));
	run_ogame();
	run_genetic();
	
}
