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
	// using ASTROPHYSICS = globals::Upgradables::ASTROPHYSICS;
	// using COLONIZATION_SHIP = globals::Upgradables::COLONIZATION_SHIP;
	Simulation sim = Simulation();
	auto out = sim.run(chromosome);
	auto poz1 = std::find(chromosome.begin(), chromosome.end(), static_cast<int>(globals::Upgradables::ASTROPHYSICS));
	auto poz2 = std::find(chromosome.begin(), chromosome.end(), static_cast<int>(globals::Upgradables::COLONIZATION_SHIP));

	double time = out[0];
	double points = out[1];
	double loaded_resources = out[2];
	// if (time == 0 || time > 1000 * 3600)
	// {
	// 	return 1e-100;
	// }
	if (time == 0 || points == 0 || loaded_resources == 0 || chromosome.size() > 200)
	{
		return 1e-100;
	}
	else if(poz1 == chromosome.end() || poz2 == chromosome.end())
	{
		time = 1e99;
	}
	return 1.0 / time;
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
