//
// Created by Paweł Kulig on 2019-02-08.
//

#ifndef OGAME_PLANET_H
#define OGAME_PLANET_H

#include "BuildQueue.h"
#include "Resources.h"
#include "common_includes.h"
#include "simple_structures.h"
#include <memory>

class Planet {
private:
	double time = 0;
	double points = 0;
	double loaded_resources = 0;
	std::array<std::unique_ptr<GameObject>, static_cast<int>(globals::Upgradables::SIZE)> structure_list;
	BuildQueue buildQueue;

    Resources resources;
	const int planet_temperature;
	int nanite_factory_level = 0;

	//Production factor is based on avaliable energy on planet
    double productionFactor;

	bool can_upgrade_shipyard = true;
	bool can_upgrade_laboratory = true;

	void construct_structure_list();

public:
    Planet();

	template <class T>
	T get_structure(int index) const
	{
	    if (index < static_cast<int>(globals::Upgradables::SIZE))
		{
			auto temp = dynamic_cast<T>(structure_list[index].get());
			if (temp)
			{
	        	return temp;
			}
			throw(std::runtime_error("Planet::get_structure incorrect type cast!"));
		}
		throw(std::runtime_error("Planet::get_structure incorrect index!"));
	}

	template <class T>
	T get_structure(globals::Upgradables index) const
	{
	    int lindex = static_cast<int>(index);
	    if (lindex < static_cast<int>(globals::Upgradables::SIZE))
	    {
			auto temp = dynamic_cast<T>(structure_list[lindex].get());
			if (temp) {
				return temp;
			}
			throw(std::runtime_error("Planet::get_structure incorrect type cast!"));

	    }
	    throw(std::runtime_error("Planet::get_structure incorrect index!"));
	}


    void passTime(double);
	int upgrade_structure(int structure_index);
	void finish_queues();
    Resources getPlanetExtraction() const;
	double getTimeToLoadResources(int structure_index);

    int calculatePlanetEnergy() const;
	Resources getPlanetEnergyProduction() const;
    Resources getResources() const;
	void calculateProductionFactor();
    double getProductionFactor() const;
	int get_nanite_factory_level() const;
	int get_robot_factory_level() const;
	int get_laboratory_level() const;
	int get_shipyard_level() const;
	int get_planet_temperature() const;
	double getTime() const;
	double getPoints() const;
	double getLoadedResources() const;
	double get_construction_time(int structure_index) const;
};


#endif //OGAME_PLANET_H
