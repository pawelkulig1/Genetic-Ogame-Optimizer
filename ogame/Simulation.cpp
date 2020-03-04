//
// Created by Paweł Kulig on 2019-02-08.
//

#include "Simulation.h"
#include <stdexcept>

Simulation::Simulation() : m_planet(Planet()) {
    time = 0;
}

double Simulation::run() {
    double tempTime;
    for (const int structure_index : m_queue) {
        tempTime = m_planet.getTimeToBuild(structure_index);
        time += tempTime;
        m_planet.passTime(tempTime);

        if (!m_planet.upgrade_structure(structure_index)) {
			std::runtime_error("Simulation::run(): unable to upgrade structure");
        }
		Structure *structure = m_planet.get_structure(structure_index);
		time += structure->getConstructionTime(m_planet.get_robot_factory_level(), m_planet.get_nanite_factory_level());
    }
	return time;
}
