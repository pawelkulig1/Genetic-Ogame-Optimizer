#include "Simulation.h"
#include "utility.h"
#include "basic_crossover_operator.h"
#include "random_generators.h"

std::vector<globals::Upgradables> example_queue();

double run_simulation(std::vector<int> chromosome);


int main() {
	RandomGenerators::get_instance();
	srand(time(NULL));
	Utility util = Utility();
	util.set_fitness_function(&run_simulation);
	
	Crossover<int> *crossover_strategy = new BasicCrossoverOperator<int>();
	util.set_crossover_strategy(*crossover_strategy);

	util.run();
	delete crossover_strategy;
    return 0;
}


double run_simulation(std::vector<int> chromosome)
{
	Simulation sim = Simulation();
	auto score = 1.0/sim.run(chromosome);
	return score;
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
