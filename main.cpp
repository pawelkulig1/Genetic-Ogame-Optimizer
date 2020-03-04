#include "Simulation.h"

std::vector<globals::Upgradables> example_queue();


int main() {
    Simulation simulation = Simulation();
	auto vec = example_queue();
	simulation.set_queue(vec);
	std::cout << simulation.run() << std::endl;;
    return 0;
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
