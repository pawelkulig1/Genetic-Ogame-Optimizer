//
// Created by Paweł Kulig on 2019-02-08.
//

#include "Simulation.h"
#include <stdexcept>

Simulation::Simulation() : m_planet(Planet()) {
    time = 0;
}

double Simulation::run(std::vector<int> queue) {
    double tempTime;
    for (const int structure_index : queue) {
        tempTime = m_planet.getTimeToBuild(structure_index);
		if (tempTime == -1)
		{
			time += 1e100;
			break;
		}
        time += tempTime;
        m_planet.passTime(tempTime);
		int status = m_planet.upgrade_structure(structure_index);
        if (status == 1) {
			throw(std::runtime_error("Simulation::run(): unable to upgrade structure"));
        }
		else if (status == 2) {
			time += 1e100;
		}

		Structure *structure = m_planet.get_structure(structure_index);
		time += structure->getConstructionTime(m_planet.get_robot_factory_level(), m_planet.get_nanite_factory_level());
    }
	return time;
}
