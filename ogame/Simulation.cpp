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
    // bool finish = false;
    // for(int i =0;i<queue.size();i++) {
    //     std::cout << queue[i] << ", ";
    // }
    // std::cout << std::endl;
    double bonus = 0;
    int iteration = 0;
    for (const int structure_index : queue) {
        
        iteration++;
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
    }
    planet.finish_queues();
    if (planet.getTime() + bonus < 100)
    {
        std::cout << "we have error in simulation there!" << std::endl;
    }
    return planet.getTime() + bonus;
}
