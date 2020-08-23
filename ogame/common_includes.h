#pragma once

namespace globals {
    enum Upgradables
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
        	
        //TECHNOLOGIES
        ASTROPHYSICS         = 11,
        ESPIONAGE_TECHNOLOGY = 12,
        COMBUSTION_DRIVE     = 13,
        IMPULSE_DRIVE        = 14,
        ENERGY_TECHNOLOGY    = 15,

        //SHIPS
        SOLAR_SATELLITE   = 16,
        COLONIZATION_SHIP = 17,
        SMALL_CARGO       = 18,
        
        SIZE
    };

    enum QueueIndex
    {
        NONE 	   = -1,
        BUILDING   =  0,
        TECHNOLOGY =  1,
        SHIP       =  2,
        END
    };

    static constexpr int SAFETY_GUARD = 1;
}
