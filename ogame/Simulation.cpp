//
// Created by Paweł Kulig on 2019-02-08.
//

#include "Simulation.h"
#include <stdexcept>
#include <fstream>

Simulation::Simulation() {
    time = 0;
}

double Simulation::run(std::vector<int> queue) {
    Planet planet = Planet();
    // bool finish = false;
    std::fstream file;
    file.open("log.out", std::ios::out);
    for(int i =0;i<queue.size();i++) {
         file << queue[i] << ", ";
    }
    file.close();
    int iteration = 0;
    for (const int structure_index : queue) {
        
        iteration++;
        int status = planet.upgrade_structure(structure_index);

        if (status == 1) {
            throw(std::runtime_error("Simulation::run(): unable to upgrade structure"));
        }
        else if (status == 2) {
			// std::cout << "status 2" << std::endl;
            return 1e100;
        }
        else if (status == 3) {
			// std::cout << "status 3" << std::endl;
            return 1e100;
        }
    }
    planet.finish_queues();

    return planet.getTime();
}
