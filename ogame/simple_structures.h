#pragma once
#include "Technology.h"
#include "Building.h"
// class Building;
// class Technology;

#define simple_structure(class_name, parent_class_name, obj_name, default_cost, ratio, requirements, additional_functions) \
class class_name : public parent_class_name \
{ \
public: \
    class_name(Resources defaultCost = default_cost, double costRatio = ratio) : \
        parent_class_name(defaultCost, costRatio) \
    { \
        name = obj_name; \
        requirements \
    } \
    additional_functions \
    virtual ~class_name() {} \
};

#define construct_requirements(name, lvl) m_requirements.push_back(std::make_pair(static_cast<int>(globals::Upgradables::name), lvl));

//Buildings
simple_structure(NaniteFactory, Building, "Nanite Factory", Resources(1e6, 5e5, 1e5, 0.0), 2.0,
                construct_requirements(ROBOT_FACTORY, 10)
                construct_requirements(ASTROPHYSICS, 10), ;)

simple_structure(Terraformer, Building, "Terraformer", Resources(0, 5e4, 1e5, 1000), 2.0,
                construct_requirements(NANITE_FACTORY, 1)
                construct_requirements(ENERGY_TECHNOLOGY, 12),
                int get_aditional_fields() {
                    //1 -> 5 /+5
                    //2 -> 11 /+6
                    //3 -> 16 /+5
                    //4 -> 22 /+6...
                    return getLvl() % 2 == 0 ?
                        (getLvl() / 2.0) * 11 - getLvl() :
                        ((getLvl() - 1) / 2.0) * 11 + 5 - getLvl();
                })

simple_structure(AlianceDepot, Building, "Alliance Depot", Resources(2e4, 4e4, 0.0, 0.0), 2.0, ;, ;)

simple_structure(MissleSilo, Building, "Missle Silo", Resources(2e4, 2e4, 1e3, 0.0), 2.0,
                construct_requirements(SHIPYARD, 1),
                int get_missle_slots() {
                    return getLvl() * 10;
                })

//Technologies

simple_structure(ComputerTechnology, Technology, "Computer Technology", Resources(0, 400, 600, 0), 2,
                construct_requirements(LABORATORY, 1), ;)

simple_structure(WeaponsTechnology, Technology, "Weapons Technology", Resources(800, 200, 0, 0), 2,
                construct_requirements(LABORATORY, 4),
                double get_attack_bonus() {
                    return 0.1 * getLvl();
                })

simple_structure(ShieldingTechnology, Technology, "Shielding Technology", Resources(200, 600, 0, 0), 2,
                construct_requirements(LABORATORY, 6)
                construct_requirements(ENERGY_TECHNOLOGY, 3),
                double get_shield_bonus() {
                    return 0.1 * getLvl();
                })

simple_structure(ArmourTechnology, Technology, "Armour Technology", Resources(1e3, 0, 0, 0), 2,
                construct_requirements(LABORATORY, 2),
                double get_armour_bonus() {
                    return 0.1 * getLvl();
                })

simple_structure(HyperspaceTechnology, Technology, "Hyperspace Technology", Resources(0, 4e3, 2e3, 0), 2,
                construct_requirements(LABORATORY, 7)
                construct_requirements(SHIELDING_TECHNOLOGY, 5)
                construct_requirements(ENERGY_TECHNOLOGY, 5),
                double get_cargo_bonus() {
                    return 0.05 * getLvl();
                })

simple_structure(HyperspaceDrive, Technology, "Hyperspace Drive", Resources(10e3, 20e3, 6e3, 0), 2,
                construct_requirements(LABORATORY, 7)
                construct_requirements(ENERGY_TECHNOLOGY, 5)
                construct_requirements(SHIELDING_TECHNOLOGY, 5)
                construct_requirements(HYPERSPACE_TECHNOLOGY, 3),
                double get_speed_bonus() {
                    return 0.3 * getLvl();
                })

simple_structure(LaserTechnology, Technology, "Laser Technology", Resources(200, 100, 0, 0), 2,
                construct_requirements(LABORATORY, 1)
                construct_requirements(ENERGY_TECHNOLOGY, 2), ;)

simple_structure(IonTechnology, Technology, "Ion Technology", Resources(1000, 300, 100, 0), 2,
                construct_requirements(LABORATORY, 4)
                construct_requirements(LASER_TECHNOLOGY, 5)
                construct_requirements(ENERGY_TECHNOLOGY, 4),
                double get_deconstruction_discount() {
                    return 0.04 * getLvl();
                })

simple_structure(PlasmaTechnology, Technology, "Plasma Technology", Resources(2e3, 4e3, 1e3, 0), 2,
                construct_requirements(LABORATORY, 4)
                construct_requirements(LASER_TECHNOLOGY, 10)
                construct_requirements(ENERGY_TECHNOLOGY, 8)
                construct_requirements(ION_TECHNOLOGY, 5),
                Resources get_extraction_bonus() {
                    return Resources(0.01, 0.0066, 0.0033) * getLvl();
                })

simple_structure(IntergalacticReasearchNetwork, Technology, "Intergalactic Research Network", Resources(240e3, 400e3, 160e3, 0), 2,
                construct_requirements(LABORATORY, 10)
                construct_requirements(COMPUTER_TECHNOLOGY, 8)
                construct_requirements(HYPERSPACE_TECHNOLOGY, 8),
                int get_max_connected_labs() {
                    return getLvl() + 1;
                })

simple_structure(GravitonTechnology, Technology, "Graviton Technology", Resources(0, 0, 0, 3e5), 2,
                construct_requirements(LABORATORY, 12),
                double getConstructionTime(int labolatory_level, int not_important=0) const final {
                    return 1;
                })
