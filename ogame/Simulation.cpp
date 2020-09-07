//
// Created by Paweł Kulig on 2019-02-08.
//

#include "Simulation.h"
#include <stdexcept>
#include <fstream>
#include <algorithm>
#include <numeric>
// #include <chrono>

Simulation::Simulation() {
    time = 0;
}

std::vector<double> Simulation::run(std::vector<int> queue) {
    constexpr int globals_size = static_cast<int>(globals::Upgradables::SIZE);

    int max = *std::max_element(queue.begin(), queue.end());
    int number_of_planets = (max / globals_size) + 1;

    std::vector<Planet> planets;
    //planets.reserve(number_of_planets);
    // auto start = std::chrono::steady_clock::now();
    for(int i{0}; i<number_of_planets;i++) {planets.push_back(Planet());}
    // auto end = std::chrono::steady_clock::now();
    // std::chrono::duration<double> elapsed = end - start;
    // std::cout << "timing1: " << elapsed.count()  << '\n';

    // start = std::chrono::steady_clock::now();
    int iteration = 0;
    for (const int structure_index : queue) {
        int planet_index = structure_index / globals_size;
        int command_index = structure_index % globals_size;
        iteration++;
        int status = planets[planet_index].upgrade_structure(command_index);

        if (status == 1) {
            throw(std::runtime_error("Simulation::run(): unable to upgrade structure"));
        }
        else if (status == 2) {
			// std::cout << "status 2" << std::endl;
            return {0, 0, 0};
        }
        else if (status == 3) {
			// std::cout << "status 3" << std::endl;
            return {0, 0, 0};
        }
    }
    // end = std::chrono::steady_clock::now();
    // elapsed = end - start;
    // std::cout << "timing2: " << elapsed.count()  << '\n';
    double total_points = 0; //planets[0].getPoints();
    double total_resources = 0; //planets[0].getLoadedResources();
    double total_time = 0; //planets[0].getTime();

    for_each(planets.begin(), planets.end(), [](Planet &p){p.finish_queues();});
    total_time = std::max_element(planets.begin(), planets.end(), [](const Planet& p1, const Planet& p2){return p1.getTime() < p2.getTime();})->getTime();
    std::for_each(planets.begin(), planets.end(), [&total_points](const Planet& p) {total_points += p.getPoints();});
    std::for_each(planets.begin(), planets.end(), [&total_resources](const Planet& p){total_resources += p.getLoadedResources();});
    return {total_time, total_points, total_resources}; //TODO
}
