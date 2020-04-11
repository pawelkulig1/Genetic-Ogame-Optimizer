#include "Simulation.h"
#include "utility.h"
#include "basic_crossover_operator.h"
#include "random_generators.h"

std::vector<globals::Upgradables> example_queue();

double run_simulation(Chromosome chromosome);


int main() {
	RandomGenerators::get_instance();
	srand(time(NULL));
	Utility util = Utility();
	util.set_fitness_function(&run_simulation);
	
	BasicCrossoverOperator crossover_strategy = BasicCrossoverOperator();
	util.set_crossover_strategy(crossover_strategy);

	util.run();
	//util.print();

    return 0;
}


double run_simulation(Chromosome chromosome)
{
	Simulation sim = Simulation();
	return 1/sim.run(chromosome.get_vector());
}

std::vector<globals::Upgradables> example_queue()
{
    std::vector<globals::Upgradables> queue;

	queue.push_back(globals::Upgradables::METAL_MINE);
	queue.push_back(globals::Upgradables::SOLAR_PLANT);
	queue.push_back(globals::Upgradables::METAL_MINE);
	queue.push_back(globals::Upgradables::METAL_MINE);
	queue.push_back(globals::Upgradables::SOLAR_PLANT);
	queue.push_back(globals::Upgradables::SOLAR_PLANT);
	queue.push_back(globals::Upgradables::CRYSTAL_MINE);
	queue.push_back(globals::Upgradables::METAL_MINE);
	queue.push_back(globals::Upgradables::CRYSTAL_MINE);
	queue.push_back(globals::Upgradables::SOLAR_PLANT);
	queue.push_back(globals::Upgradables::METAL_MINE);
	queue.push_back(globals::Upgradables::SOLAR_PLANT);
	queue.push_back(globals::Upgradables::CRYSTAL_MINE);
	queue.push_back(globals::Upgradables::METAL_MINE);
	queue.push_back(globals::Upgradables::CRYSTAL_MINE);
	queue.push_back(globals::Upgradables::METAL_MINE);
	queue.push_back(globals::Upgradables::SOLAR_PLANT);
	queue.push_back(globals::Upgradables::CRYSTAL_MINE);
	queue.push_back(globals::Upgradables::METAL_MINE);
	queue.push_back(globals::Upgradables::CRYSTAL_MINE);
	queue.push_back(globals::Upgradables::METAL_MINE);
	queue.push_back(globals::Upgradables::CRYSTAL_MINE);
	queue.push_back(globals::Upgradables::METAL_MINE);
	return queue;
}
