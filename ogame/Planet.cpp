//
// Created by Paweł Kulig on 2019-02-08.
//

#include "Planet.h"
#include <math.h>
#include "common_includes.h"
#include <algorithm>
#include <iostream>

Planet::Planet() : metalMine(MetalMine()),
                   crystalMine(CrystalMine()),
                   deuteriumMine(DeuteriumMine(25)),
                   solarPlant(SolarPlant()),
				   fusion_plant(FusionPlant()),
				   laboratory(Laboratory()),
				   robot_factory(RobotFactory()),
				   shipyard(Shipyard()),

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
	structure_list[4] = &fusion_plant;
	structure_list[5] = &laboratory;
	structure_list[6] = &robot_factory;
	structure_list[7] = &shipyard;
}

void Planet::passTime(double seconds) {
	Resources current_extraction = getPlanetExtraction();
	//std::cout<<"current_extraction: " << current_extraction << std::endl;
	resources.setMetal(resources.at(0) + (current_extraction.at(0) / 3600) * seconds);
	resources.setCrystal(resources.at(1) + (current_extraction.at(1) / 3600) * seconds);
	resources.setDeuterium(resources.at(2) + (current_extraction.at(2) / 3600) * seconds);
	//std::cout<<"resources: " << resources << " seconds: " << seconds << std::endl;
	
    //resources = resources + (getPlanetExtraction() / 3600) * seconds;
}

int Planet::upgrade_structure(int structure_index)
{
	Structure *structure = structure_list[structure_index];
    Resources upgradeCost = structure->getNextLevelCost();

	//check if meets requirements
	for (Structure::Requirements req: structure->get_requirements())
	{
		if (structure_list[req.first]->getLvl() < req.second)
		{
			return 2;
		}
	}
	
    if (resources >= upgradeCost) {
        resources = resources - upgradeCost;

        //add resources loaded during building time
        resources = resources + (getPlanetExtraction() / 3600) * structure->getConstructionTime(get_robot_factory_level(), nanite_factory_level);

        structure->operator++();
        resources.setEnergy(calculatePlanetEnergy());

        //calculate production factor
			
        if (metalMine.getEnergyConsumption().at(3) +
            crystalMine.getEnergyConsumption().at(3) +
            deuteriumMine.getEnergyConsumption().at(3) == 0)
		{
            productionFactor = 1;
			return 0;
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

        return 0;
    }
	//std::cout<<"Unable to build because: resources: " << resources << " upgradeCost: " << upgradeCost << std::endl;
    return 1;
	
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

	//std::cout << structure_index << cost_delta << " " << extraction << std::endl;
	if (cost_delta.at(2) < 0 && extraction.at(2) == 0.0) {
		return -1;
	}
	

	if (cost_delta.at(0) >= 0 && cost_delta.at(1) >= 0 && cost_delta.at(2) >= 0)
		return 0;
		
	Resources::data_type temp[3] = {(cost_delta.at(0) / extraction.at(0)),
		   							(cost_delta.at(1) / extraction.at(1)),
									(cost_delta.at(2) / extraction.at(2))};

	//std::cout << temp[0] << " " << temp[1] << " " << temp[2] << std::endl;
	return abs(*std::min_element(temp, temp+3)) * 3600 + 1;
}

Resources Planet::getPlanetExtraction() const {
	double fusion_consumption = fusion_plant.getProductionPerHour().at(2);
	if (deuteriumMine.getProductionPerHour().at(2) * static_cast<double>(productionFactor) < fusion_plant.getProductionPerHour().at(2))
	{
		fusion_consumption = 0;
	}

	//std::cout << "fusion consumption: "<< fusion_consumption << " " << "deuterium production: " << deuteriumMine.getProductionPerHour() << " " << static_cast<double>(productionFactor) << " " << deuteriumMine.getDefaultProductionPerHour().at(2) << " " << fusion_consumption << std::endl;

	Resources temp = Resources(
            (metalMine.getProductionPerHour() * static_cast<double>(productionFactor) + metalMine.getDefaultProductionPerHour()).at(0),
            (crystalMine.getProductionPerHour() * static_cast<double>(productionFactor) + crystalMine.getDefaultProductionPerHour()).at(1),
            (deuteriumMine.getProductionPerHour() * static_cast<double>(productionFactor) + 
			 	deuteriumMine.getDefaultProductionPerHour()).at(2) - 
				fusion_consumption,
            calculatePlanetEnergy());
	//std::cout<<temp << std::endl;
	return temp;

}

Resources &Planet::getResources() {
    return resources;
}

int Planet::calculatePlanetEnergy() const {
	Resources fusion_additional_energy = Resources(0, 0, 0, fusion_plant.getProductionPerHour().at(3));
	if (deuteriumMine.getDefaultProductionPerHour().at(2) < fusion_plant.getProductionPerHour().at(2))
	{
		fusion_additional_energy.setEnergy(0);
	}

    return (solarPlant.getProductionPerHour() 
			+ fusion_additional_energy
		  	- metalMine.getEnergyConsumption()
		   	- crystalMine.getEnergyConsumption()
		   	- deuteriumMine.getEnergyConsumption()).at(3);
}

int Planet::get_robot_factory_level() const
{
	return robot_factory.getLvl();
}

int Planet::get_nanite_factory_level() const
{
	return nanite_factory_level;
}

int Planet::get_planet_temperature() const
{
	return planet_temperature;
}
