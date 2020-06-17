#include <assert.h>
#include "MetalMine.h"
#include "SolarPlant.h"
#include "CrystalMine.h"
#include "DeuteriumMine.h"
#include "Simulation.h"
#include <cassert>

bool test_mines_cost()
{
	SolarPlant s = SolarPlant();
	assert(s.getUpgradeCost().getMetal() == 75);
	assert(s.getUpgradeCost().getCrystal() == 30);
	assert(s.getUpgradeCost().getDeuterium() == 0);
	assert(s.getUpgradeCost().getEnergy() == 0);

	MetalMine m = MetalMine();
	assert(m.getUpgradeCost().getMetal() == 60);
	assert(m.getUpgradeCost().getCrystal() == 15);
	assert(m.getUpgradeCost().getDeuterium() == 0);
	assert(m.getUpgradeCost().getEnergy() == 0);

	CrystalMine c = CrystalMine();
	assert(c.getUpgradeCost().getMetal() == 48);
	assert(c.getUpgradeCost().getCrystal() == 24);
	assert(c.getUpgradeCost().getDeuterium() == 0);
	assert(c.getUpgradeCost().getEnergy() == 0);
	
	DeuteriumMine d = DeuteriumMine();
	assert(d.getUpgradeCost().getMetal() == 225);
	assert(d.getUpgradeCost().getCrystal() == 75);
	assert(d.getUpgradeCost().getDeuterium() == 0);
	assert(d.getUpgradeCost().getEnergy() == 0);

	return true;
}

bool test_upgrade_time()
{
	SolarPlant s = SolarPlant();
	assert(s.getConstructionTime(0, 0) == 3600 * (s.getUpgradeCost().getMetal() + s.getUpgradeCost().getCrystal()) / 2500);

	MetalMine m = MetalMine();
	assert(m.getConstructionTime(0, 0) == 3600 * (m.getUpgradeCost().getMetal() + m.getUpgradeCost().getCrystal()) / 2500);

	CrystalMine c = CrystalMine();
	assert(c.getConstructionTime(0, 0) == 3600 * (c.getUpgradeCost().getMetal() + c.getUpgradeCost().getCrystal()) / 2500);
	
	DeuteriumMine d = DeuteriumMine();
	assert(d.getConstructionTime(0, 0) == 3600 * (d.getUpgradeCost().getMetal() + d.getUpgradeCost().getCrystal()) / 2500);
	return true;
}

bool test_upgrade()
{
	std::vector<int> in = {2, 6, 11, 0, 0, 2, 10, 3, 10, 0, 2, 2, 6, 9, 1, 11, 7, 8, 11, 10, 10};
	Simulation sim = Simulation();
	assert(sim.run(in) == 1e100);

	in = {3, 3, 0, 2, 0, 3, 1, 0, 0, 3, 1, 3, 0, 1, 0, 3, 0, 1, 6, 1, 2};
	std::cout<<sim.run(in)<<std::endl;

	in = {2, 10, 10, 7, 10, 7, 2, 3, 0, 10, 10, 8, 9, 1, 7, 6, 0, 11, 1, 7, 11};
	std::cout<<sim.run(in)<<std::endl;
}

bool test_queues()
{
	std::vector<int> in = {0, 3, 0, 0, 3, 1, 3, 0, 3, 0};
	Simulation sim = Simulation();
	double out = sim.run(in);
	in = {0, 3, 1, 2, 5, 5, 5, 9, 0};
	sim.run(in);
	
	// std::cout << out << std::endl;
}

bool test_my_queue()
{
	std::vector<int> in = {3,0,2,1,3,1,1,0,0,3,0,1,3,2,6,0,5,8,6,6,4,8,5,13,7,2,11,13,6,12,6,10,7,4,3,1,12,8,5,10,12,4,12,0,0,8,12,13,7,3,0,13,0,10,4,7,13,6,7,10,5,5,6,5,2,0,11,4,12,13,3,10,13,5,8,9,8,11,11,12,5,4,13,0,8,10,3,11,0,9,6,9,0,8,11,1,5,3,6,12,7,6,12,2,0,7,7,3,5,5,2,8,0,2,11,4,10,2,0,8,12,7,5,0,1,4,12,11,13,12,12,0,11,3,7,8,0,12,7,2,3,11,5,5,9,10,9,9,7,0};
	Simulation sim = Simulation();
	double out = sim.run(in);
	std::cout << out << std::endl;
}
