//
// Created by Paweł Kulig on 2019-02-08.
//

#ifndef OGAME_PLANET_H
#define OGAME_PLANET_H

#include "BuildQueue.h"

#include "DeuteriumMine.h"
#include "SolarPlant.h"
#include "FusionPlant.h"
#include "CrystalMine.h"
#include "MetalMine.h"
#include "Laboratory.h"
#include "RobotFactory.h"
#include "Shipyard.h"
#include "MetalStorage.h"
#include "CrystalStorage.h"
#include "DeuteriumStorage.h"

#include "Astrophysics.h"
#include "EspionageTechnology.h"
#include "ImpulseDrive.h"
#include "EnergyTechnology.h"

#include "SolarSatellite.h"
#include "ColonizationShip.h"

#include "common_includes.h"

class Planet {
private:
	double time = 0;

	//Buildings
    MetalMine metalMine;
    CrystalMine crystalMine;
    DeuteriumMine deuteriumMine;
    SolarPlant solarPlant;
	FusionPlant fusion_plant;
	Laboratory laboratory;
	RobotFactory robot_factory;
	Shipyard shipyard;

	MetalStorage metal_storage;
	CrystalStorage crystal_storage;
	DeuteriumStorage deuterium_storage;

	//Technologies
	Astrophysics astrophysics;
	EspionageTechnology espionage_technology;
	ImpulseDrive impulse_drive;
	EnergyTechnology energy_technology;

	//Ships
	SolarSatellite solar_satellite;
	ColonizationShip colonization_ship;

	GameObject *structure_list[globals::Upgradables::SIZE];
	BuildQueue buildQueue;

    Resources resources;
	const int planet_temperature = 25;
	int nanite_factory_level = 0;
	
	//Production factor is based on avaliable energy on planet
    double productionFactor;

	void construct_structure_list();

public:
    Planet();

	GameObject *get_structure(int index);
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
	int get_planet_temperature() const;
	double getTime() const;
};


#endif //OGAME_PLANET_H
