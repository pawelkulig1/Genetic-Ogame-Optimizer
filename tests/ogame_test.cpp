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

bool test_my_queue2()
{
	std::vector<int> in = {2, 2, 2, 2, 0, 2, 3, 2, 0, 1, 1, 2, 1, 2, 2, 1, 2, 2, 3, 2, 1, 2, 0, 1, 1, 3, 0, 1, 1, 0, 3, 
  3, 2, 2, 2, 1, 2, 3, 1, 0, 2, 1, 2, 2, 0, 3, 1, 1, 0, 2, 1, 3, 3, 1, 2, 0, 3, 1, 2, 2, 0, 0, 3, 0, 3, 1, 3, 0, 0, 1, 3, 2, 3, 0, 2, 0, 2, 
  3, 2, 3, 3, 2, 1, 0, 2, 3, 0, 3, 3, 0, 0, 2, 0, 0, 2, 0, 2, 1, 0, 1, 0, 0, 1, 2, 3, 2, 0, 2, 2, 3, 3, 3, 1, 2, 2, 0, 3, 1, 1, 3, 0, 2, 3, 
  3, 0, 0, 0, 2, 1, 0, 3, 1, 1, 0, 3, 1, 0, 2, 3, 2, 0, 3, 3, 3, 2, 0, 3, 3, 2, 2, 1, 0, 1, 0, 3, 2, 0, 3, 1, 2, 2, 3, 0, 2, 3, 0, 3, 1, 0, 
  3, 3, 3, 0, 3, 1, 1, 0, 3, 0, 3, 0, 1, 3, 3, 1, 1, 0, 3, 0, 0, 3, 3, 0, 2, 0, 3, 2, 0, 3, 2};
	Simulation sim = Simulation();
	double out = sim.run(in);
	std::cout << out << std::endl;
}

bool test_my_queue3()
{
	std::vector<int> in = {9, 6, 0, 2, 13, 1, 3, 1, 1, 2, 0, 12, 3, 0, 0, 3, 0, 0, 3, 2, 2, 5, 16, 2, 2, 0, 2, 6, 0, 2, 
  3, 1, 0, 0, 1, 3, 2, 1, 14, 2, 1, 1, 1, 1, 2, 8, 9, 6, 8, 14, 5, 3, 12, 2, 1, 2, 2, 3, 10, 1, 2, 1, 1, 1, 2, 3, 15, 0, 12, 7, 3, 7, 6, 6, 
  2, 12, 14, 4, 8, 4, 15, 13, 12, 15, 11, 16};
	Simulation sim = Simulation();
	double out = sim.run(in);
	std::cout << out << std::endl;
}

bool test_my_queue4()
{
	std::vector<int> in = {3,1,0,1,0,1,1,0,1,3,1,0,3,1,2,3,2,0,2,2,0,1,0,3,3,1,1,3,0,2,1,3,2,2,0,1,2,3,0,2,3,1,0,0,1,1,2,
	1,0,1,1,0,0,1,2,3,3,3,0,2,0,3,0,2,2,0,2,3,3,0,0,0,3,2,1,0,2,1,2,0,2,3,1,2,2,0,2,0,1,1,3,2,3,2,2,0,0,3,3,2,1,2,1,0,2,2,
	3,3,2,1,1,2,2,2,2,3,1,0,3,2,1,0,3,0,1,0,2,2,0,1,3,2,3,0,0,1,0,1,0,1,3,2,0,0,3,3,2,1,0,2,0,3,0,3,2,0,0,1,0,3,3,3,1,3,3,1,
	3,0,1,3,2,3,2,0,2,2,3,2,1,0,0,2,0,3,0,0,3,2,1,2,1,0,1,0,0,2,2,10,15,7};
	Simulation sim = Simulation();
	double out = sim.run(in);
	std::cout << out << std::endl;
}

bool test_my_queue5()
{
	std::vector<int> in = {0, 0, 0, 2, 2, 3, 1, 3, 11, 3, 0, 1, 0, 0, 3, 2, 0, 1, 1, 2, 1, 1, 3, 3, 2, 0, 1, 1, 1, 3, 2, 2, 0, 2, 0, 
	1, 0, 1, 1, 2, 3, 2, 2, 0, 1, 0, 2, 0, 3, 1, 1, 3, 3, 2, 0, 0, 2, 0, 1, 0, 1, 2, 3, 0, 1, 0, 1, 0, 2, 1, 0, 1, 0, 2, 0, 3, 1, 0, 
	2, 1, 2, 2, 3, 2, 3, 2, 3, 0, 1, 3, 3, 1, 3, 3, 1, 2, 3, 0, 0, 2, 3, 2, 2, 0, 3, 2, 2, 1, 3, 2, 2, 2, 3, 3, 2, 3, 1, 2, 1, 3, 2, 
	1, 2, 2, 2, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 2, 3, 2, 2, 3, 1, 2, 0, 3, 3, 0, 2, 1, 2, 3, 0, 0, 2, 1, 3, 0, 3, 0, 3, 3, 3, 3, 
	3, 2, 0, 3, 0, 0, 0, 2, 2, 1, 0, 0, 0, 1, 2, 3, 0, 1, 0, 0, 3, 2, 0, 2, 0, 1, 2, 3, 0, 3, 0, 0, 0, 3, 3, 2};
	Simulation sim = Simulation();
	double out = sim.run(in);
	std::cout << out << std::endl;
}

bool test_my_queue6()
{
	std::vector<int> in = {0};
	Simulation sim = Simulation();
	double out = sim.run(in);
	std::cout << out << std::endl;
}

bool test_my_queue()
{
	std::vector<int> in = {6, 5, 0, 0, 2, 5, 2, 4, 5, 4, 5, 1, 9, 8, 1, 6, 6, 0, 6, 4, 16};
	Simulation sim = Simulation();
	double out = sim.run(in);
	std::cout << out << std::endl;
}
