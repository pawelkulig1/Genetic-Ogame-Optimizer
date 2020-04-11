//
// Created by Paweł Kulig on 2019-02-08.
//

#ifndef OGAME_PLANET_H
#define OGAME_PLANET_H


#include "DeuteriumMine.h"
#include "SolarPlant.h"
#include "FusionPlant.h"
#include "CrystalMine.h"
#include "MetalMine.h"
#include "Laboratory.h"
#include "RobotFactory.h"
#include "Shipyard.h"
#include "common_includes.h"

class Planet {
private:
    MetalMine metalMine;
    CrystalMine crystalMine;
    DeuteriumMine deuteriumMine;
    SolarPlant solarPlant;
	FusionPlant fusion_plant;
	Laboratory laboratory;
	RobotFactory robot_factory;
	Shipyard shipyard;

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
    void passTime(double);
	int upgrade_structure(int structure_index);
    Resources getPlanetExtraction() const;
	double getTimeToBuild(int structure_index);

    int calculatePlanetEnergy() const;

    Resources &getResources();

    double getProductionFactor() const;

	int get_nanite_factory_level() const;

	int get_robot_factory_level() const;

	int get_planet_temperature() const;
};


#endif //OGAME_PLANET_H
