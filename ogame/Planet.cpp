//
// Created by Paweł Kulig on 2019-02-08.
//

#include "Planet.h"
#include <math.h>
#include "common_includes.h"
#include <algorithm>
#include <iostream>

Planet::Planet() : planet_temperature(75),
                   metalMine(MetalMine()),
                   crystalMine(CrystalMine()),
                   deuteriumMine(DeuteriumMine(75)),
                   solarPlant(SolarPlant()),
                   fusion_plant(FusionPlant()),
                   laboratory(Laboratory()),
                   robot_factory(RobotFactory()),
                   shipyard(Shipyard()),
                   metal_storage(MetalStorage()),
                   crystal_storage(CrystalStorage()),
                   deuterium_storage(DeuteriumStorage()),

                   astrophysics(Astrophysics()),
                   espionage_technology(EspionageTechnology()),
                   combustion_drive(CombustionDrive()),
                   impulse_drive(ImpulseDrive()),
                   energy_technology(EnergyTechnology()),

                   solar_satellite(SolarSatellite()),
                   colonization_ship(ColonizationShip()),
                   small_cargo(SmallCargo()),

                   buildQueue(BuildQueue()),
                   resources(Resources(500, 500, 0, 0)),
                   productionFactor(1) 
{
    construct_structure_list();
}

GameObject *Planet::get_structure(int index)
{
    if (index < globals::Upgradables::SIZE)
        return structure_list[index];
    else
        throw(std::runtime_error("Planet::get_structure incorrect index!"));
}

void Planet::construct_structure_list()
{
    int i = 0;
    structure_list[i++] = &metalMine; //0
    structure_list[i++] = &crystalMine;
    structure_list[i++] = &deuteriumMine;
    structure_list[i++] = &metal_storage;
    structure_list[i++] = &crystal_storage;
    structure_list[i++] = &deuterium_storage;
    structure_list[i++] = &solarPlant;
    structure_list[i++] = &fusion_plant;
    structure_list[i++] = &laboratory;
    structure_list[i++] = &robot_factory;
    structure_list[i++] = &shipyard;
    
    structure_list[i++] = &astrophysics;
    structure_list[i++] = &espionage_technology;
    structure_list[i++] = &combustion_drive;
    structure_list[i++] = &impulse_drive;
    structure_list[i++] = &energy_technology;

    structure_list[i++] = &solar_satellite;
    structure_list[i++] = &colonization_ship;
    structure_list[i++] = &small_cargo;
}

void Planet::passTime(double seconds) {
    seconds = seconds + globals::SAFETY_GUARD;
    Resources current_extraction = getPlanetExtraction();
    Resources new_resources = Resources(
        resources.at(0) + (current_extraction.at(0) / 3600) * seconds,
        resources.at(1) + (current_extraction.at(1) / 3600) * seconds,
        resources.at(2) + (current_extraction.at(2) / 3600) * seconds
        );

    if (metal_storage.getStorageCapacity().getMetal() < new_resources.getMetal()){
        new_resources.setMetal(metal_storage.getStorageCapacity().getMetal());
    }

    if (crystal_storage.getStorageCapacity().getCrystal() < new_resources.getCrystal()){
        new_resources.setCrystal(crystal_storage.getStorageCapacity().getCrystal());
    }

    if (deuterium_storage.getStorageCapacity().getDeuterium() < new_resources.getDeuterium()){
        new_resources.setDeuterium(deuterium_storage.getStorageCapacity().getDeuterium());
    }

    resources.setMetal(new_resources.getMetal());
    resources.setCrystal(new_resources.getCrystal());
    resources.setDeuterium(new_resources.getDeuterium());
    buildQueue.passTime(seconds);

    time += seconds;
}

int Planet::upgrade_structure(int structure_index)
{
    GameObject* structure = structure_list[structure_index];
    Resources upgradeCost = structure->getUpgradeCost();

    if (!can_upgrade_laboratory && structure_index == globals::Upgradables::LABORATORY)
    {
        buildQueue.lockQueue(globals::QueueIndex::BUILDING, buildQueue.getTime(globals::QueueIndex::TECHNOLOGY));
    }

    if (!can_upgrade_shipyard && structure_index == globals::Upgradables::SHIPYARD)
    {
        buildQueue.lockQueue(globals::QueueIndex::BUILDING, buildQueue.getTime(globals::QueueIndex::SHIP));
    }
    
    double construction_time = get_construction_time(structure_index);
    const int queue_index = structure->getQueueIndex();
    double time_to_closest_upgrade = buildQueue.getShortestTime();
    double time_to_load_resources = getTimeToLoadResources(structure_index);

    if (time_to_load_resources == -1 && buildQueue.isEmpty(-1))
    {
        return 3; //cannot build because resources won't be able to load in finite time
    }
    
    while(!buildQueue.isEmpty(queue_index) || !(getTimeToLoadResources(structure_index) == 0))
    {
        if (getTimeToLoadResources(structure_index) == -1 && buildQueue.isEmpty(-1)) {
            return 3;
        }
        time_to_closest_upgrade = buildQueue.getShortestTime();
        // std::cout<<"time to closest upgrade: "<< time_to_closest_upgrade << std::endl;
        if (time_to_closest_upgrade <= 0 && !buildQueue.isEmpty(buildQueue.getFinishedIndex()))
        {
            buildQueue.getFinishedBuilding()->operator++();
            resources.setEnergy(calculatePlanetEnergy());
            calculateProductionFactor();

            //if two times in row these needs to be updated once again
            upgradeCost = structure->getUpgradeCost(); 
            construction_time = get_construction_time(structure_index);

            buildQueue.clearQueue(buildQueue.getFinishedIndex());
        }
        time_to_load_resources = getTimeToLoadResources(structure_index);
        time_to_closest_upgrade = buildQueue.getShortestTime();

        double time_needed = std::max(time_to_load_resources, time_to_closest_upgrade);
        if ((time_to_load_resources > 0 && time_to_closest_upgrade > 0) || (buildQueue.isEmpty(queue_index) && time_to_load_resources == 0))
        {
            time_needed = std::min(time_to_load_resources, time_to_closest_upgrade);
        }
        if (time_to_closest_upgrade == -1)
        {
            time_needed == -1;
        }
        passTime(time_needed);
    }

    //check if meets requirements
    if (structure->get_requirements().size() > 0)
    {
        for (GameObject::Requirements req: structure->get_requirements())
        {
            if (dynamic_cast<Structure*>(structure_list[req.first])->getLvl() < req.second)
            {
                return 2; //not meeting requirements
            }
        }
    }

    if (!buildQueue.addToQueue(queue_index, structure, construction_time)) {
        throw(std::runtime_error("queue not empty when upgrading!"));
    }
    
    if (resources >= upgradeCost) {
        resources = resources - upgradeCost;
    }
    else {
        throw(std::runtime_error("Not enough resources when upgrading!"));
    }

    //lock other queues for some structures:
    //1. technology if lab
    //2. lab if technology
    //3. ships if shipyard
    //4. shipyard if ship

    can_upgrade_laboratory = buildQueue.isEmpty(globals::QueueIndex::TECHNOLOGY);
    can_upgrade_shipyard = buildQueue.isEmpty(globals::QueueIndex::SHIP);
    if (structure_index == globals::Upgradables::LABORATORY)
    {
        buildQueue.lockQueue(globals::QueueIndex::TECHNOLOGY, get_construction_time(structure_index));
    }

    if (structure_index == globals::Upgradables::SHIPYARD)
    {
        buildQueue.lockQueue(globals::QueueIndex::SHIP, get_construction_time(structure_index));
    }
    return 0;
}

double Planet::get_construction_time(int structure_index) const
{
    GameObject *obj = structure_list[structure_index];
    const int queue_index = obj->getQueueIndex();
    if (queue_index == 0)
    {
        return obj->getConstructionTime(
            get_robot_factory_level(), get_nanite_factory_level());
    }
    else if (queue_index == 1)
    {
        return obj->getConstructionTime(
            get_laboratory_level(), get_nanite_factory_level());
    }
    else if (queue_index == 2)
    {
        return obj->getConstructionTime(
            get_shipyard_level(), get_nanite_factory_level());
    }
    else 
    {
        throw(std::runtime_error("get_construction_time queue index above 2"));
    }
}

void Planet::finish_queues()
{
    while(!buildQueue.isEmpty())
    {
        double time_to_closest_upgrade = buildQueue.getShortestTime();
        if (time_to_closest_upgrade <= 0)
        {
            buildQueue.getFinishedBuilding()->operator++();
            resources.setEnergy(calculatePlanetEnergy());
            calculateProductionFactor();
            buildQueue.clearQueue(buildQueue.getFinishedIndex());
        }
        passTime(time_to_closest_upgrade);
    }
}

void Planet::calculateProductionFactor()
{
    if (metalMine.getEnergyConsumption().at(3) +
        crystalMine.getEnergyConsumption().at(3) +
        deuteriumMine.getEnergyConsumption().at(3) == 0)
    {
        productionFactor = 1;
        return;
    }

    productionFactor = (
           static_cast<double>(getPlanetEnergyProduction().at(3)) /
           (
               metalMine.getEnergyConsumption().at(3) +
               crystalMine.getEnergyConsumption().at(3) +
               deuteriumMine.getEnergyConsumption().at(3)
           ));

    if (productionFactor > 1)
        productionFactor = 1;

}

double Planet::getProductionFactor() const {
    return productionFactor;
}

double Planet::getTimeToLoadResources(int structure_index)
{
    GameObject *structure = get_structure(structure_index);
    const int queue_index = structure->getQueueIndex();
    Resources upgrade_cost = structure->getUpgradeCost();
    //case when the same object is in queue and is going to be built, this means we have to calculate cost as if it was built already but production not.
    if (buildQueue.at(queue_index) == structure && queue_index != globals::QueueIndex::SHIP) {
        const int lvl = static_cast<Structure *>(structure)->getLvl();
        static_cast<Structure* >(structure)->setLvl(lvl + 1);
        upgrade_cost = structure->getUpgradeCost();
        static_cast<Structure *>(structure)->setLvl(lvl);
    }
    Resources cost_delta;
    Resources extraction = getPlanetExtraction();
    cost_delta = resources - upgrade_cost;

    if (cost_delta.at(2) < 0 && (extraction.at(2) == 0 || resources.at(2) + abs(cost_delta.at(2)) > deuterium_storage.getStorageCapacity().at(2))) {
        return -1;
    }
    
    if (cost_delta.at(1) < 0 && (extraction.at(1) == 0 || resources.at(1) + abs(cost_delta.at(1)) > crystal_storage.getStorageCapacity().at(1))) {
        return -1;
    }

    if (cost_delta.at(0) < 0 && (extraction.at(0) == 0 || resources.at(0) + abs(cost_delta.at(0)) > metal_storage.getStorageCapacity().at(0))) {
        return -1;
    }

    if (cost_delta.at(0) >= 0 && cost_delta.at(1) >= 0 && cost_delta.at(2) >= 0) {
        return 0;
    }

    Resources::data_type temp[3] = {1e100, 1e100, 1e100};
    if(extraction.at(2) != 0) temp[2] = cost_delta.at(2) / extraction.at(2);
    if(extraction.at(1) != 0) temp[1] = cost_delta.at(1) / extraction.at(1);
    if(extraction.at(0) != 0) temp[0] = cost_delta.at(0) / extraction.at(0);
    return abs(*std::min_element(temp, temp+2)) * 3600 + 1;
}

Resources Planet::getPlanetExtraction() const {
    double fusion_consumption = fusion_plant.getProductionPerHour(energy_technology.getLvl()).at(2);
    if (deuteriumMine.getProductionPerHour().at(2) * static_cast<double>(productionFactor) < fusion_plant.getProductionPerHour(energy_technology.getLvl()).at(2))
    {
        fusion_consumption = 0;
    }

    Resources temp = Resources(
            (metalMine.getProductionPerHour() * static_cast<double>(productionFactor) + metalMine.getDefaultProductionPerHour()).at(0),
            (crystalMine.getProductionPerHour() * static_cast<double>(productionFactor) + crystalMine.getDefaultProductionPerHour()).at(1),
            (deuteriumMine.getProductionPerHour() * static_cast<double>(productionFactor) + 
                 deuteriumMine.getDefaultProductionPerHour()).at(2) - 
                fusion_consumption,
            calculatePlanetEnergy());
    
    if (metal_storage.getStorageCapacity().getMetal() <= getResources().getMetal()) {
        temp.setMetal(0);
    }

    if (crystal_storage.getStorageCapacity().getCrystal() <= getResources().getCrystal()) {
        temp.setCrystal(0);
    }

    if (deuterium_storage.getStorageCapacity().getDeuterium() <= getResources().getDeuterium()) {
        temp.setDeuterium(0);
    }
    return temp;
}

Resources Planet::getResources() const {
    return resources;
}

Resources Planet::getPlanetEnergyProduction() const
{
		
    Resources fusion_additional_energy = Resources(0, 0, 0, fusion_plant.getProductionPerHour(energy_technology.getLvl()).at(3));
    if (deuteriumMine.getDefaultProductionPerHour().at(2) < fusion_plant.getProductionPerHour(energy_technology.getLvl()).at(2))
    {
        fusion_additional_energy.setEnergy(0);
    }

    return solarPlant.getProductionPerHour()
            + fusion_additional_energy
            + solar_satellite.getProductionPerHour(planet_temperature);

}
int Planet::calculatePlanetEnergy() const {
    Resources fusion_additional_energy = Resources(0, 0, 0, fusion_plant.getProductionPerHour(energy_technology.getLvl()).at(3));
    if (deuteriumMine.getDefaultProductionPerHour().at(2) < fusion_plant.getProductionPerHour(energy_technology.getLvl()).at(2))
    {
        fusion_additional_energy.setEnergy(0);
    }

    return (solarPlant.getProductionPerHour() 
            + fusion_additional_energy
            + solar_satellite.getProductionPerHour(planet_temperature)
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

int Planet::get_shipyard_level() const
{
    return shipyard.getLvl();
}

int Planet::get_laboratory_level() const
{
    return laboratory.getLvl();
}

double Planet::getTime() const
{
    return time;
}
