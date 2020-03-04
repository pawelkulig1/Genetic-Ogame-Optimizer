#include <iostream>
#include "basic_crossover_operator.h"
#include "chromosome.h"

extern bool test_mines_cost();
extern bool test_upgrade_time();
extern bool test_basic_crossover();

int main()
{
	test_mines_cost();
	test_upgrade_time();
	test_basic_crossover();

	

}
