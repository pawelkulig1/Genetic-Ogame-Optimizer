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
    Planet m_planet;
public:
    Simulation();
    std::vector<double> run(std::vector<int> queue);
};


#endif //OGAME_SIMULATION_H
