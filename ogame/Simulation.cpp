//
// Created by Paweł Kulig on 2019-02-08.
//

#include "Simulation.h"
#include <stdexcept>

Simulation::Simulation() {
    time = 0;
}

double Simulation::run(std::vector<int> queue) {
	Planet planet = Planet();
	//double time = 0;
    //double tempTime;
    for (const int structure_index : queue) {
		int status = planet.upgrade_structure(structure_index);
        if (status == 1) {
			throw(std::runtime_error("Simulation::run(): unable to upgrade structure"));
        }
		else if (status == 2) {
			return 1e100;
		}
		else if (status == 3) {
			return 1e100;
		}
		std::cout << "cumulative time: " << planet.getTime() << std::endl;
		//GameObject *structure = m_planet.get_structure(structure_index);
		//time += structure->getConstructionTime(m_planet.get_robot_factory_level(), m_planet.get_nanite_factory_level());
    }
	//std::cout<<time<<std::endl;
	return planet.getTime();
}
