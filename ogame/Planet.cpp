//
// Created by Paweł Kulig on 2019-02-08.
//

#include "Planet.h"
#include <cmath>
#include "common_includes.h"
#include <algorithm>
#include <iostream>

Planet::Planet() : metalMine(MetalMine()),
                   crystalMine(CrystalMine()),
                   deuteriumMine(DeuteriumMine(25)),
                   solarPlant(SolarPlant()),
                   resources(Resources(500, 500, 0, 0)),
                   productionFactor(1) 
{
	construct_structure_list();
}

Structure *Planet::get_structure(int index)
{
	if (index < globals::Upgradables::SIZE)
		return structure_list[index];
	else
		throw(std::runtime_error("Planet::get_structure incorrect index!"));
}


void Planet::construct_structure_list()
{
	structure_list[0] = &metalMine;
	structure_list[1] = &crystalMine;
	structure_list[2] = &deuteriumMine;
	structure_list[3] = &solarPlant;
}

void Planet::passTime(int seconds) {
	Resources current_extraction = getPlanetExtraction();
	resources.setMetal(resources.at(0) + (current_extraction.at(0) / 3600) * seconds);
	resources.setCrystal(resources.at(1) + (current_extraction.at(1) / 3600) * seconds);
	resources.setDeuterium(resources.at(2) + (current_extraction.at(2) / 3600) * seconds);
	
    //resources = resources + (getPlanetExtraction() / 3600) * seconds;
}

bool Planet::upgrade_structure(int structure_index)
{
	Structure *structure = structure_list[structure_index];
    Resources upgradeCost = structure->getNextLevelCost();
    if (resources >= upgradeCost) {

        resources = resources - upgradeCost;

        //add resources loaded during building time
        resources = resources + (getPlanetExtraction() / 3600) * structure->getConstructionTime(robot_factory_level, nanite_factory_level);

        structure->operator++();
        resources.setEnergy(calculatePlanetEnergy());

        //calculate production factor
			
        if (metalMine.getEnergyConsumption().at(3) +
            crystalMine.getEnergyConsumption().at(3) +
            deuteriumMine.getEnergyConsumption().at(3) == 0)
		{
            productionFactor = 1;
			return true;
		}
		productionFactor = (
           	static_cast<double>(solarPlant.getProductionPerHour().at(3)) /
           	(
           	    metalMine.getEnergyConsumption().at(3) +
           	    crystalMine.getEnergyConsumption().at(3) +
           	    deuteriumMine.getEnergyConsumption().at(3)
           	));

		//productionFactor = 1.0;


        if (productionFactor > 1)
            productionFactor = 1;

        return true;
    }
    return false;
	
}

double Planet::getProductionFactor() const {
    return productionFactor;
}

double Planet::getTimeToBuild(int structure_index)
{
	Structure *structure = get_structure(structure_index);
    Resources cost_delta;
    Resources extraction = getPlanetExtraction();
    cost_delta = resources - structure->getNextLevelCost();

	if (cost_delta.at(0) >= 0 && cost_delta.at(1) >= 0 && cost_delta.at(2) >= 0)
		return 0;
	
	Resources::data_type temp[3] = {abs(cost_delta.at(0) / extraction.at(0)),
		   							abs(cost_delta.at(1) / extraction.at(1)),
									abs(cost_delta.at(2) / extraction.at(2))};
	return *std::max_element(temp, temp+2) * 3600 + 1;
}

Resources Planet::getPlanetExtraction() {
    return Resources(
            (metalMine.getProductionPerHour() * static_cast<double>(productionFactor) + metalMine.getDefaultProductionPerHour()).at(0),
            (crystalMine.getProductionPerHour() * static_cast<double>(productionFactor) + crystalMine.getDefaultProductionPerHour()).at(1),
            (deuteriumMine.getProductionPerHour() * static_cast<double>(productionFactor) + deuteriumMine.getDefaultProductionPerHour()).at(
                    2),
            calculatePlanetEnergy());

	//return retResources;
}

MetalMine &Planet::getMetalMine() {
    return metalMine;
}

CrystalMine &Planet::getCrystalMine() {
    return crystalMine;
}

DeuteriumMine &Planet::getDeuteriumMine() {
    return deuteriumMine;
}

SolarPlant &Planet::getSolarPlant() {
    return solarPlant;
}

Resources &Planet::getResources() {
    return resources;
}

int Planet::calculatePlanetEnergy() {
    return (solarPlant.getProductionPerHour() - metalMine.getEnergyConsumption() -
            crystalMine.getEnergyConsumption() - deuteriumMine.getEnergyConsumption()).at(3);
}

int Planet::get_robot_factory_level() const
{
	return robot_factory_level;
}

int Planet::get_nanite_factory_level() const
{
	return nanite_factory_level;
}

int Planet::get_planet_temperature() const
{
	return planet_temperature;
}
