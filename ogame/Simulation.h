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
    std::vector<globals::Upgradables> m_queue;
    Planet m_planet;
public:
    Simulation();
	void set_queue(std::vector<globals::Upgradables> &queue) {m_queue = queue;}
    double run();
};


#endif //OGAME_SIMULATION_H
