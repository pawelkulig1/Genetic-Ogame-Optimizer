//
// Created by Paweł Kulig on 2019-02-08.
//

#ifndef OGAME_SIMULATION_H
#define OGAME_SIMULATION_H


#include <vector>
#include "Building.h"
#include "Planet.h"

class Simulation {
private:
    double time;
    std::vector<Building> queue;
    Planet planet;
public:
    Simulation();

    void run();
};


#endif //OGAME_SIMULATION_H
