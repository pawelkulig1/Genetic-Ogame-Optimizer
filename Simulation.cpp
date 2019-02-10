//
// Created by Paweł Kulig on 2019-02-08.
//

#include "Simulation.h"

Simulation::Simulation() : planet(Planet()) {
    time = 0;
}

void Simulation::run() {
    double tempTime;
    std::vector<Building *> queue;
    queue.push_back(&planet.getSolarPlant());
    queue.push_back(&planet.getMetalMine());
    queue.push_back(&planet.getMetalMine());
    queue.push_back(&planet.getSolarPlant());
    queue.push_back(&planet.getMetalMine());
    queue.push_back(&planet.getCrystalMine());
    queue.push_back(&planet.getSolarPlant());
    queue.push_back(&planet.getMetalMine());
    queue.push_back(&planet.getCrystalMine());
    queue.push_back(&planet.getMetalMine());
    queue.push_back(&planet.getSolarPlant());
    queue.push_back(&planet.getMetalMine());
    queue.push_back(&planet.getMetalMine());
    queue.push_back(&planet.getMetalMine());
    queue.push_back(&planet.getMetalMine());
    queue.push_back(&planet.getMetalMine());

    for (Building *building : queue) {
        if (!planet.upgradeBuilding(*building)) {
            tempTime = planet.getTimeToBuild(*building);
            time += tempTime;
            planet.passTime(tempTime);
        }
        time += building->getConstructionTime();
        std::cout << *building << std::endl;
        std::cout << time / 3600 << std::endl;
    }
}
