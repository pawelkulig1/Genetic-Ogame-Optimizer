//
// Created by Paweł Kulig on 2019-02-08.
//

#include "Planet.h"
#include <math.h>
#include "common_includes.h"
#include <algorithm>
#include <iostream>
#include <functional>
#include <memory>
#include "GameObject.h"
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
#include "CombustionDrive.h"
#include "ImpulseDrive.h"
#include "EnergyTechnology.h"

#include "SolarSatellite.h"
#include "ColonizationShip.h"
#include "SmallCargo.h"


Planet::Planet() : planet_temperature(75),
                   buildQueue(BuildQueue()),
                   resources(Resources(500, 500, 0, 0)),
                   productionFactor(1)
{
    construct_structure_list();
}

void Planet::construct_structure_list()
{
    int i = 0;
    // MetalMine mm = MetalMine();
    structure_list[i++] = std::make_unique<MetalMine>(MetalMine());//metalMine; //0
    structure_list[i++] = std::make_unique<CrystalMine>(CrystalMine());
    structure_list[i++] = std::make_unique<DeuteriumMine>(DeuteriumMine());
    structure_list[i++] = std::make_unique<MetalStorage>(MetalStorage());
    structure_list[i++] = std::make_unique<CrystalStorage>(CrystalStorage());
    structure_list[i++] = std::make_unique<DeuteriumStorage>(DeuteriumStorage());
    structure_list[i++] = std::make_unique<SolarPlant>(SolarPlant());
    structure_list[i++] = std::make_unique<FusionPlant>(FusionPlant());
    structure_list[i++] = std::make_unique<Laboratory>(Laboratory());
    structure_list[i++] = std::make_unique<RobotFactory>(RobotFactory());
    structure_list[i++] = std::make_unique<Shipyard>(Shipyard());

    structure_list[i++] = std::make_unique<Astrophysics>(Astrophysics());
    structure_list[i++] = std::make_unique<EspionageTechnology>(EspionageTechnology());
    structure_list[i++] = std::make_unique<CombustionDrive>(CombustionDrive());
    structure_list[i++] = std::make_unique<ImpulseDrive>(ImpulseDrive());
    structure_list[i++] = std::make_unique<EnergyTechnology>(EnergyTechnology());

    structure_list[i++] = std::make_unique<SolarSatellite>(SolarSatellite());
    structure_list[i++] = std::make_unique<ColonizationShip>(ColonizationShip());
    structure_list[i++] = std::make_unique<SmallCargo>(SmallCargo());
}

void Planet::passTime(double seconds) {
    auto metal_storage = get_structure<MetalStorage* >(globals::Upgradables::METAL_STORAGE);// _list[];
    auto crystal_storage = get_structure<CrystalStorage*>(globals::Upgradables::CRYSTAL_STORAGE);
    auto deuterium_storage = get_structure<DeuteriumStorage*>(globals::Upgradables::DEUTERIUM_STORAGE);

    seconds = seconds + globals::SAFETY_GUARD;
    Resources current_extraction = getPlanetExtraction();
    Resources new_resources = Resources(
        resources.at(0) + (current_extraction.at(0) / 3600) * seconds,
        resources.at(1) + (current_extraction.at(1) / 3600) * seconds,
        resources.at(2) + (current_extraction.at(2) / 3600) * seconds
        );

    if (metal_storage->getStorageCapacity().getMetal() < new_resources.getMetal()){
        new_resources.setMetal(metal_storage->getStorageCapacity().getMetal());
    }

    if (crystal_storage->getStorageCapacity().getCrystal() < new_resources.getCrystal()){
        new_resources.setCrystal(crystal_storage->getStorageCapacity().getCrystal());
    }

    if (deuterium_storage->getStorageCapacity().getDeuterium() < new_resources.getDeuterium()){
        new_resources.setDeuterium(deuterium_storage->getStorageCapacity().getDeuterium());
    }

    Resources delta = new_resources - resources;
    loaded_resources += delta.getMetal() + delta.getCrystal() + delta.getDeuterium();
    resources.setMetal(new_resources.getMetal());
    resources.setCrystal(new_resources.getCrystal());
    resources.setDeuterium(new_resources.getDeuterium());
    buildQueue.passTime(seconds);

    time += seconds;
}

int Planet::upgrade_structure(int structure_index)
{
    auto structure = get_structure<GameObject*>(structure_index);//structure_list[structure_index];
    Resources upgradeCost = structure->getUpgradeCost();

    if (!can_upgrade_laboratory && structure_index == static_cast<int>(globals::Upgradables::LABORATORY))
    {
        buildQueue.lockQueue(static_cast<int>(globals::QueueIndex::BUILDING), buildQueue.getTime(static_cast<int>(globals::QueueIndex::TECHNOLOGY)));
    }

    if (!can_upgrade_shipyard && structure_index == static_cast<int>(globals::Upgradables::SHIPYARD))
    {
        buildQueue.lockQueue(static_cast<int>(globals::QueueIndex::BUILDING), buildQueue.getTime(static_cast<int>(globals::QueueIndex::SHIP)));
    }

    double construction_time = get_construction_time(structure_index);
    const int queue_index = static_cast<int>(structure->getQueueIndex());
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
            time_needed = -1;
        }
        passTime(time_needed);
    }

    //check if meets requirements
    if (structure->get_requirements().size() > 0)
    {
        for (GameObject::Requirements req: structure->get_requirements())
        {
            //if (dynamic_cast<Structure*>(structure_list[req.first])->getLvl() < req.second)
            if (get_structure<Structure*>(req.first)->getLvl() < req.second)
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
        points += upgradeCost.getMetal() + upgradeCost.getCrystal() + upgradeCost.getDeuterium();
    }
    else {
        throw(std::runtime_error("Not enough resources when upgrading!"));
    }

    //lock other queues for some structures:
    //1. technology if lab
    //2. lab if technology
    //3. ships if shipyard
    //4. shipyard if ship

    can_upgrade_laboratory = buildQueue.isEmpty(static_cast<int>(globals::QueueIndex::TECHNOLOGY));
    can_upgrade_shipyard = buildQueue.isEmpty(static_cast<int>(globals::QueueIndex::SHIP));
    if (structure_index == static_cast<int>(globals::Upgradables::LABORATORY))
    {
        buildQueue.lockQueue(static_cast<int>(globals::QueueIndex::TECHNOLOGY), get_construction_time(structure_index));
    }

    if (structure_index == static_cast<int>(globals::Upgradables::SHIPYARD))
    {
        buildQueue.lockQueue(static_cast<int>(globals::QueueIndex::SHIP), get_construction_time(structure_index));
    }
    return 0;
}

double Planet::get_construction_time(int structure_index) const
{
    GameObject const * obj = get_structure<GameObject*>(structure_index);//structure_list[structure_index];
    const int queue_index = static_cast<int>(obj->getQueueIndex());
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
    auto metalMine = get_structure<MetalMine*>(globals::Upgradables::METAL_MINE);
    auto crystalMine = get_structure<CrystalMine*>(globals::Upgradables::CRYSTAL_MINE);
    auto deuteriumMine = get_structure<DeuteriumMine*>(globals::Upgradables::DEUTERIUM_MINE);
    if (metalMine->getEnergyConsumption().at(3) +
        crystalMine->getEnergyConsumption().at(3) +
        deuteriumMine->getEnergyConsumption().at(3) == 0)
    {
        productionFactor = 1;
        return;
    }

    productionFactor = (
           static_cast<double>(getPlanetEnergyProduction().at(3)) /
           (
               metalMine->getEnergyConsumption().at(3) +
               crystalMine->getEnergyConsumption().at(3) +
               deuteriumMine->getEnergyConsumption().at(3)
           ));

    if (productionFactor > 1)
        productionFactor = 1;

}

double Planet::getProductionFactor() const {
    return productionFactor;
}

double Planet::getTimeToLoadResources(int structure_index)
{
    GameObject *structure = get_structure<GameObject*>(structure_index);
    const int queue_index = static_cast<int>(structure->getQueueIndex());
    Resources upgrade_cost = structure->getUpgradeCost();
    //case when the same object is in queue and is going to be built, this means we have to calculate cost as if it was built already but production not.
    if (buildQueue.at(queue_index) == structure && queue_index != static_cast<int>(globals::QueueIndex::SHIP)) {
        const int lvl = static_cast<Structure *>(structure)->getLvl();
        static_cast<Structure* >(structure)->setLvl(lvl + 1);
        upgrade_cost = structure->getUpgradeCost();
        static_cast<Structure *>(structure)->setLvl(lvl);
    }
    Resources cost_delta;
    Resources extraction = getPlanetExtraction();
    cost_delta = resources - upgrade_cost;

    auto metal_storage = get_structure<MetalStorage*>(globals::Upgradables::METAL_STORAGE);
    auto crystal_storage = get_structure<CrystalStorage*>(globals::Upgradables::CRYSTAL_STORAGE);
    auto deuterium_storage = get_structure<DeuteriumStorage*>(globals::Upgradables::DEUTERIUM_STORAGE);

    if (cost_delta.at(2) < 0 && (extraction.at(2) == 0 || resources.at(2) + abs(cost_delta.at(2)) > deuterium_storage->getStorageCapacity().at(2))) {
        return -1;
    }

    if (cost_delta.at(1) < 0 && (extraction.at(1) == 0 || resources.at(1) + abs(cost_delta.at(1)) > crystal_storage->getStorageCapacity().at(1))) {
        return -1;
    }

    if (cost_delta.at(0) < 0 && (extraction.at(0) == 0 || resources.at(0) + abs(cost_delta.at(0)) > metal_storage->getStorageCapacity().at(0))) {
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
    auto fusion_plant = get_structure<FusionPlant*>(globals::Upgradables::FUSION_PLANT);
    auto energy_technology = get_structure<EnergyTechnology*>(globals::Upgradables::ENERGY_TECHNOLOGY);
    auto metalMine = get_structure<MetalMine*>(globals::Upgradables::METAL_MINE);
    auto crystalMine = get_structure<CrystalMine*>(globals::Upgradables::CRYSTAL_MINE);
    auto deuteriumMine = get_structure<DeuteriumMine*>(globals::Upgradables::DEUTERIUM_MINE);
    auto metal_storage = get_structure<MetalStorage*>(globals::Upgradables::METAL_STORAGE);
    auto crystal_storage = get_structure<CrystalStorage*>(globals::Upgradables::CRYSTAL_STORAGE);
    auto deuterium_storage = get_structure<DeuteriumStorage*>(globals::Upgradables::DEUTERIUM_STORAGE);

    double fusion_consumption = fusion_plant->getProductionPerHour(energy_technology->getLvl()).at(2);
    if (deuteriumMine->getProductionPerHour().at(2) * static_cast<double>(productionFactor) < fusion_plant->getProductionPerHour(energy_technology->getLvl()).at(2))
    {
        fusion_consumption = 0;
    }

    Resources temp = Resources(
            (metalMine->getProductionPerHour() * static_cast<double>(productionFactor) + metalMine->getDefaultProductionPerHour()).at(0),
            (crystalMine->getProductionPerHour() * static_cast<double>(productionFactor) + crystalMine->getDefaultProductionPerHour()).at(1),
            (deuteriumMine->getProductionPerHour() * static_cast<double>(productionFactor) +
                 deuteriumMine->getDefaultProductionPerHour()).at(2) -
                fusion_consumption,
            calculatePlanetEnergy());

    if (metal_storage->getStorageCapacity().getMetal() <= getResources().getMetal()) {
        temp.setMetal(0);
    }

    if (crystal_storage->getStorageCapacity().getCrystal() <= getResources().getCrystal()) {
        temp.setCrystal(0);
    }

    if (deuterium_storage->getStorageCapacity().getDeuterium() <= getResources().getDeuterium()) {
        temp.setDeuterium(0);
    }
    return temp;
}

Resources Planet::getResources() const {
    return resources;
}

Resources Planet::getPlanetEnergyProduction() const
{
    auto fusion_plant = get_structure<FusionPlant*>(globals::Upgradables::FUSION_PLANT);
    auto energy_technology = get_structure<EnergyTechnology*>(globals::Upgradables::ENERGY_TECHNOLOGY);
    auto deuteriumMine = get_structure<DeuteriumMine*>(globals::Upgradables::DEUTERIUM_MINE);
    auto solar_satellite = get_structure<SolarSatellite*>(globals::Upgradables::SOLAR_SATELLITE);
    auto solarPlant = get_structure<SolarPlant*>(globals::Upgradables::SOLAR_PLANT);

    Resources fusion_additional_energy = Resources(0, 0, 0, fusion_plant->getProductionPerHour(energy_technology->getLvl()).at(3));
    if (deuteriumMine->getDefaultProductionPerHour().at(2) < fusion_plant->getProductionPerHour(energy_technology->getLvl()).at(2))
    {
        fusion_additional_energy.setEnergy(0);
    }

    return solarPlant->getProductionPerHour()
            + fusion_additional_energy
            + solar_satellite->getProductionPerHour(planet_temperature);

}
int Planet::calculatePlanetEnergy() const {
    auto fusion_plant = get_structure<FusionPlant*>(globals::Upgradables::FUSION_PLANT);
    auto energy_technology = get_structure<EnergyTechnology*>(globals::Upgradables::ENERGY_TECHNOLOGY);
    auto metalMine = get_structure<MetalMine*>(globals::Upgradables::METAL_MINE);
    auto crystalMine = get_structure<CrystalMine*>(globals::Upgradables::CRYSTAL_MINE);
    auto deuteriumMine = get_structure<DeuteriumMine*>(globals::Upgradables::DEUTERIUM_MINE);
    auto solarPlant = get_structure<SolarPlant*>(globals::Upgradables::SOLAR_PLANT);
    auto solar_satellite = get_structure<SolarSatellite*>(globals::Upgradables::SOLAR_SATELLITE);

    Resources fusion_additional_energy = Resources(0, 0, 0, fusion_plant->getProductionPerHour(energy_technology->getLvl()).at(3));
    if (deuteriumMine->getDefaultProductionPerHour().at(2) < fusion_plant->getProductionPerHour(energy_technology->getLvl()).at(2))
    {
        fusion_additional_energy.setEnergy(0);
    }

    return (solarPlant->getProductionPerHour()
            + fusion_additional_energy
            + solar_satellite->getProductionPerHour(planet_temperature)
            - metalMine->getEnergyConsumption()
            - crystalMine->getEnergyConsumption()
            - deuteriumMine->getEnergyConsumption()).at(3);
}

int Planet::get_robot_factory_level() const
{
    return get_structure<RobotFactory*>(globals::Upgradables::ROBOT_FACTORY)->getLvl();
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
    return get_structure<Shipyard*>(globals::Upgradables::SHIPYARD)->getLvl();
}

int Planet::get_laboratory_level() const
{
    return get_structure<Laboratory*>(globals::Upgradables::LABORATORY)->getLvl();
}

double Planet::getTime() const
{
    return time;
}

double Planet::getPoints() const
{
    return points;
}

double Planet::getLoadedResources() const
{
    return loaded_resources;
}
