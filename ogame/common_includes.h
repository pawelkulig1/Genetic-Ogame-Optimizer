#pragma once

namespace globals {
	enum Upgradables
	{
		//BUILDINGS
		METAL_MINE     = 0,
		CRYSTAL_MINE   = 1,
		DEUTERIUM_MINE = 2,
		SOLAR_PLANT    = 3,	
		FUSION_PLANT   = 4,
		LABORATORY	   = 5,
		ROBOT_FACTORY  = 6,
		SHIPYARD	   = 7,


		//TECHNOLOGIES
		ASTROPHYSICS   = 8,
		ESPIONAGE_TECHNOLOGY = 9,
		IMPULSE_DRIVE  = 10,
		ENERGY_TECHNOLOGY = 11,

		//SHIPS
		SOLAR_SATELLITE = 12,
		COLONIZATION_SHIP = 13,
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


