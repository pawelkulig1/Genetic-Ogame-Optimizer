#pragma once

namespace globals {
    inline constexpr int max_number_of_planets = 1;

    enum class Upgradables
    {
        //BUILDINGS
        METAL_MINE        = 0,
        CRYSTAL_MINE      = 1,
        DEUTERIUM_MINE    = 2,
        METAL_STORAGE     = 3,
        CRYSTAL_STORAGE   = 4,
        DEUTERIUM_STORAGE = 5,
        SOLAR_PLANT       = 6,
        FUSION_PLANT      =	7,
        LABORATORY	      =	8,
        ROBOT_FACTORY     = 9,
        SHIPYARD	      = 10,
        NANITE_FACTORY    = 11,
        TERRAFORMER           ,
        ALIANCE_DEPOT         ,
        MISSLE_SILO           ,

        //TECHNOLOGIES
        ESPIONAGE_TECHNOLOGY ,
        COMPUTER_TECHNOLOGY  ,
        WEAPONS_TECHNOLOGY   ,
        SHIELDING_TECHNOLOGY ,
        ARMOUR_TECHNOLOGY    ,
        ENERGY_TECHNOLOGY    ,
        HYPERSPACE_TECHNOLOGY,
        COMBUSTION_DRIVE     ,
        IMPULSE_DRIVE        ,
        HYPERSPACE_DRIVE     ,
        LASER_TECHNOLOGY     ,
        ION_TECHNOLOGY       ,
        PLASMA_TECHNOLOGY    ,
        INTERGALACTIC_RESEARCH_NETWORK,
        GRAVITON_TECHNOLOGY  ,
        ASTROPHYSICS         = 30,

        //SHIPS
        SOLAR_SATELLITE  ,
        COLONIZATION_SHIP,
        SMALL_CARGO      ,

        SIZE
    };

    enum class QueueIndex
    {
        NONE 	   = -1,
        BUILDING   =  0,
        TECHNOLOGY =  1,
        SHIP       =  2,
        END
    };

    inline constexpr int SAFETY_GUARD = 1;
}
