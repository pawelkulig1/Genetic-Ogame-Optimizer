//
// Created by Paweł Kulig on 2019-02-08.
//

#include "Simulation.h"

Simulation::Simulation() : planet(Planet()) {
    time = 0;
}

void Simulation::run() {
    double tempTime;
	namespace up = globals;
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

    for (const int structure_index : queue) {
        tempTime = planet.getTimeToBuild(structure_index);
		std::cout<<"TempTime: " << tempTime << std::endl;
        time += tempTime;
        planet.passTime(tempTime);

        if (!planet.upgrade_structure(structure_index)) {
			std::cout<<"Upgrade failed!" << std::endl;	
			std::cout<<planet.getResources() << " " << planet.get_structure(structure_index)->getNextLevelCost() << std::endl;
        }
		Structure *structure = planet.get_structure(structure_index);
		time += structure->getConstructionTime(planet.get_robot_factory_level(), planet.get_nanite_factory_level());
        std::cout << *structure << std::endl;
        std::cout << time / 3600 << std::endl;
    }
}
