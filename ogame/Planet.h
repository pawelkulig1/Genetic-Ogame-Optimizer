//
// Created by Paweł Kulig on 2019-02-08.
//

#ifndef OGAME_PLANET_H
#define OGAME_PLANET_H


#include "DeuteriumMine.h"
#include "SolarPlant.h"
#include "CrystalMine.h"
#include "MetalMine.h"
#include "RobotFactory.h"
#include "Laboratory.h"
#include "common_includes.h"

class Planet {
private:
    MetalMine metalMine;
    CrystalMine crystalMine;
    DeuteriumMine deuteriumMine;
    SolarPlant solarPlant;
	Laboratory laboratory;
	RobotFactory robot_factory;
	Structure *structure_list[globals::Upgradables::SIZE];

    Resources resources;
	const int planet_temperature = 25;
	int nanite_factory_level = 0;
	
	//Production factor is based on avaliable energy on planet
    double productionFactor;

	void construct_structure_list();

public:
    Planet();

	Structure *get_structure(int index);
    void passTime(int);
	bool upgrade_structure(int structure_index);
    Resources getPlanetExtraction();
	double getTimeToBuild(int structure_index);

    int calculatePlanetEnergy();

    Resources &getResources();

    double getProductionFactor() const;

	int get_nanite_factory_level() const;

	int get_robot_factory_level() const;

	int get_planet_temperature() const;
};


#endif //OGAME_PLANET_H
