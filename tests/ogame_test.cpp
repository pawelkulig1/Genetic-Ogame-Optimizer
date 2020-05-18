#include <assert.h>
#include "MetalMine.h"
#include "SolarPlant.h"
#include "CrystalMine.h"
#include "DeuteriumMine.h"
#include "Simulation.h"

bool test_mines_cost()
{
	SolarPlant s = SolarPlant();
	assert(s.getNextLevelCost().getMetal() == 75);
	assert(s.getNextLevelCost().getCrystal() == 30);
	assert(s.getNextLevelCost().getDeuterium() == 0);
	assert(s.getNextLevelCost().getEnergy() == 0);

	MetalMine m = MetalMine();
	assert(m.getNextLevelCost().getMetal() == 60);
	assert(m.getNextLevelCost().getCrystal() == 15);
	assert(m.getNextLevelCost().getDeuterium() == 0);
	assert(m.getNextLevelCost().getEnergy() == 0);

	CrystalMine c = CrystalMine();
	assert(c.getNextLevelCost().getMetal() == 48);
	assert(c.getNextLevelCost().getCrystal() == 24);
	assert(c.getNextLevelCost().getDeuterium() == 0);
	assert(c.getNextLevelCost().getEnergy() == 0);
	
	DeuteriumMine d = DeuteriumMine();
	assert(d.getNextLevelCost().getMetal() == 225);
	assert(d.getNextLevelCost().getCrystal() == 75);
	assert(d.getNextLevelCost().getDeuterium() == 0);
	assert(d.getNextLevelCost().getEnergy() == 0);

	return true;
}

bool test_upgrade_time()
{
	SolarPlant s = SolarPlant();
	assert(s.getConstructionTime(0, 0) == 3600 * (s.getNextLevelCost().getMetal() + s.getNextLevelCost().getCrystal()) / 2500);

	MetalMine m = MetalMine();
	assert(m.getConstructionTime(0, 0) == 3600 * (m.getNextLevelCost().getMetal() + m.getNextLevelCost().getCrystal()) / 2500);

	CrystalMine c = CrystalMine();
	assert(c.getConstructionTime(0, 0) == 3600 * (c.getNextLevelCost().getMetal() + c.getNextLevelCost().getCrystal()) / 2500);
	
	DeuteriumMine d = DeuteriumMine();
	assert(d.getConstructionTime(0, 0) == 3600 * (d.getNextLevelCost().getMetal() + d.getNextLevelCost().getCrystal()) / 2500);
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

