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

void test_upgrade()
{
	std::vector<int> in = {2, 6, 11, 0, 0, 2, 10, 3, 10, 0, 2, 2, 6, 9, 1, 11, 7, 8, 11, 10, 10};
	Simulation sim = Simulation();
	assert(sim.run(in) == 1e100);

	in = {3, 3, 0, 2, 0, 3, 1, 0, 0, 3, 1, 3, 0, 1, 0, 3, 0, 1, 6, 1, 2};
	std::cout<<sim.run(in)<<std::endl;

	in = {2, 10, 10, 7, 10, 7, 2, 3, 0, 10, 10, 8, 9, 1, 7, 6, 0, 11, 1, 7, 11};
	std::cout<<sim.run(in)<<std::endl;
}

void test_robot_factory_speedup()
{
	std::vector<int> in = {0, 6, 6, 0, 2, 2};
	Planet planet = Planet();
	for (int s: in){
		planet.upgrade_structure(s);
	}
	double first = planet.get_construction_time(0);
	planet.upgrade_structure(9);
	planet.finish_queues();
	double second = planet.get_construction_time(0);
	assert(second == first * (1/2.0));
	
	planet.upgrade_structure(9);
	planet.finish_queues();
	double third = planet.get_construction_time(0);
	assert(third == second * (2/3.0));
}

void test_robot_factory_not_affecting_others()
{
	std::vector<int> in = {0, 6, 6, 0, 2, 2, 8, 10};
	Planet planet = Planet();
	for (int s: in){
		planet.upgrade_structure(s);
	}
	planet.finish_queues();
	double first_l = planet.get_construction_time(14);
	double first_s = planet.get_construction_time(15);
	planet.upgrade_structure(9);
	planet.finish_queues();
	double second_l = planet.get_construction_time(14);
	double second_s = planet.get_construction_time(15);
	assert(second_l == first_l);
	assert(second_s == first_s);
}

void test_simultaneous_queues()
{

}

void test_queues()
{
	std::vector<int> in = {0, 3, 0, 0, 3, 1, 3, 0, 3, 0};
	Simulation sim = Simulation();
	double out = sim.run(in);
	in = {0, 3, 1, 2, 5, 5, 5, 9, 0};
	sim.run(in);
	
	// std::cout << out << std::endl;
}

void test_my_queue2()
{
	std::vector<int> in = {2, 2, 2, 2, 0, 2, 3, 2, 0, 1, 1, 2, 1, 2, 2, 1, 2, 2, 3, 2, 1, 2, 0, 1, 1, 3, 0, 1, 1, 0, 3, 
  3, 2, 2, 2, 1, 2, 3, 1, 0, 2, 1, 2, 2, 0, 3, 1, 1, 0, 2, 1, 3, 3, 1, 2, 0, 3, 1, 2, 2, 0, 0, 3, 0, 3, 1, 3, 0, 0, 1, 3, 2, 3, 0, 2, 0, 2, 
  3, 2, 3, 3, 2, 1, 0, 2, 3, 0, 3, 3, 0, 0, 2, 0, 0, 2, 0, 2, 1, 0, 1, 0, 0, 1, 2, 3, 2, 0, 2, 2, 3, 3, 3, 1, 2, 2, 0, 3, 1, 1, 3, 0, 2, 3, 
  3, 0, 0, 0, 2, 1, 0, 3, 1, 1, 0, 3, 1, 0, 2, 3, 2, 0, 3, 3, 3, 2, 0, 3, 3, 2, 2, 1, 0, 1, 0, 3, 2, 0, 3, 1, 2, 2, 3, 0, 2, 3, 0, 3, 1, 0, 
  3, 3, 3, 0, 3, 1, 1, 0, 3, 0, 3, 0, 1, 3, 3, 1, 1, 0, 3, 0, 0, 3, 3, 0, 2, 0, 3, 2, 0, 3, 2};
	Simulation sim = Simulation();
	double out = sim.run(in);
	assert(out == 1e100);
	// std::cout << out << std::endl;
}

void test_my_queue3()
{
	std::vector<int> in = {9, 6, 0, 2, 13, 1, 3, 1, 1, 2, 0, 12, 3, 0, 0, 3, 0, 0, 3, 2, 2, 5, 16, 2, 2, 0, 2, 6, 0, 2, 
  3, 1, 0, 0, 1, 3, 2, 1, 14, 2, 1, 1, 1, 1, 2, 8, 9, 6, 8, 14, 5, 3, 12, 2, 1, 2, 2, 3, 10, 1, 2, 1, 1, 1, 2, 3, 15, 0, 12, 7, 3, 7, 6, 6, 
  2, 12, 14, 4, 8, 4, 15, 13, 12, 15, 11, 16};
	Simulation sim = Simulation();
	double out = sim.run(in);
	assert(out == 1e100);
	// std::cout << out << std::endl;
}

void test_my_queue4()
{
	std::vector<int> in = {3,1,0,1,0,1,1,0,1,3,1,0,3,1,2,3,2,0,2,2,0,1,0,3,3,1,1,3,0,2,1,3,2,2,0,1,2,3,0,2,3,1,0,0,1,1,2,
	1,0,1,1,0,0,1,2,3,3,3,0,2,0,3,0,2,2,0,2,3,3,0,0,0,3,2,1,0,2,1,2,0,2,3,1,2,2,0,2,0,1,1,3,2,3,2,2,0,0,3,3,2,1,2,1,0,2,2,
	3,3,2,1,1,2,2,2,2,3,1,0,3,2,1,0,3,0,1,0,2,2,0,1,3,2,3,0,0,1,0,1,0,1,3,2,0,0,3,3,2,1,0,2,0,3,0,3,2,0,0,1,0,3,3,3,1,3,3,1,
	3,0,1,3,2,3,2,0,2,2,3,2,1,0,0,2,0,3,0,0,3,2,1,2,1,0,1,0,0,2,2,10,15,7};
	Simulation sim = Simulation();
	double out = sim.run(in);
	assert(out == 1e100);
	// std::cout << out << std::endl;
}

void test_my_queue5()
{
	std::vector<int> in = {0, 0, 0, 2, 2, 3, 1, 3, 11, 3, 0, 1, 0, 0, 3, 2, 0, 1, 1, 2, 1, 1, 3, 3, 2, 0, 1, 1, 1, 3, 2, 2, 0, 2, 0, 
	1, 0, 1, 1, 2, 3, 2, 2, 0, 1, 0, 2, 0, 3, 1, 1, 3, 3, 2, 0, 0, 2, 0, 1, 0, 1, 2, 3, 0, 1, 0, 1, 0, 2, 1, 0, 1, 0, 2, 0, 3, 1, 0, 
	2, 1, 2, 2, 3, 2, 3, 2, 3, 0, 1, 3, 3, 1, 3, 3, 1, 2, 3, 0, 0, 2, 3, 2, 2, 0, 3, 2, 2, 1, 3, 2, 2, 2, 3, 3, 2, 3, 1, 2, 1, 3, 2, 
	1, 2, 2, 2, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 2, 3, 2, 2, 3, 1, 2, 0, 3, 3, 0, 2, 1, 2, 3, 0, 0, 2, 1, 3, 0, 3, 0, 3, 3, 3, 3, 
	3, 2, 0, 3, 0, 0, 0, 2, 2, 1, 0, 0, 0, 1, 2, 3, 0, 1, 0, 0, 3, 2, 0, 2, 0, 1, 2, 3, 0, 3, 0, 0, 0, 3, 3, 2};
	Simulation sim = Simulation();
	double out = sim.run(in);
	assert(out == 1e100);
	// std::cout << out << std::endl;
}

void test_my_queue6()
{
	std::vector<int> in = {0};
	Simulation sim = Simulation();
	double out = sim.run(in);
	assert(out == 109);
	// std::cout << out << std::endl;
}

void test_my_queue7()
{
	std::vector<int> in = {6, 5, 0, 0, 2, 5, 2, 4, 5, 4, 5, 1, 9, 8, 1, 6, 6, 0, 6, 4, 16}; //1e100 - requirements
	Simulation sim = Simulation();
	double out = sim.run(in);
	assert(out == 1e100);
	// std::cout << out << std::endl;
}

void test_my_queue8()
{
	std::vector<int> in = {1, 1, 0, 0, 6, 6, 6, 6, 1, 4, 6, 1, 5, 0, 0, 0, 5, 6, 2, 6, 6, 0, 2, 0, 9, 2, 2, 1, 1, 1, 5, 1, 6, 1, 14, 1, 13, 6, 6, 
	13, 12, 13, 2, 2, 12, 1, 12, 7, 12, 12, 7, 7, 7, 4, 16, 3, 11, 15, 16, 1, 16, 6, 3, 10, 10, 16, 15, 13, 4, 12, 15, 14, 2, 12, 6, 14, 6, 16, 15, 
	11, 6, 1, 8, 0, 0, 12, 12, 11, 5, 2, 2, 11, 13, 16, 14, 8, 15, 6, 6, 5, 15, 3, 3, 3, 14, 13, 14, 2, 3, 7, 11, 9, 15, 11, 5, 15, 10, 0, 8, 14, 10, 
	3, 16, 9, 13, 16, 16, 12, 12, 16, 16, 10, 4, 3, 6, 7, 14, 12, 7, 6, 4, 8, 11, 2, 4, 9, 2, 12, 1, 11, 2, 9, 1, 14, 16, 12, 14, 9, 16, 12, 14, 4, 3, 
	13, 6, 5, 16, 2, 9, 13, 11, 6, 12, 6, 5, 14, 9, 9, 13, 9, 3, 10, 0, 5, 5, 16, 12, 7, 3, 10, 7, 8, 4, 3, 10, 0, 16, 10, 2, 12};
	Simulation sim = Simulation();
	double out = sim.run(in);
	assert(out == 1e100);
	// std::cout << out << std::endl;
}

void test_my_queue9()
{
	std::vector<int> in = {5, 0, 0, 1, 5, 4, 3, 4, 5, 1, 4, 6, 6, 2, 5, 14, 12, 10, 10, 8, 10, 12, 13, 8, 13, 1, 8, 1, 5, 0, 4, 4, 0, 2, 2, 2, 2, 7, 8, 8, 12, 4, 9, 7, 9, 9, 12, 6, 6, 1, 9, 14, 12, 10, 4, 0, 14, 13, 10, 0, 12, 7, 15, 9, 11, 0, 4, 2, 3, 0, 1, 4, 6, 11, 9, 1, 10, 10, 7, 11, 14, 3, 16, 2, 16, 14, 7, 12, 3, 1, 10, 4, 13, 16, 10, 11, 15, 12, 6, 15, 3, 7, 14, 9, 15, 12, 10, 2, 16, 13, 15, 3, 15, 9, 0, 11, 9, 15, 1, 6, 14, 0, 3, 8, 1, 4, 6, 14, 12, 12, 10, 14, 2, 3, 8, 11, 0, 7, 8, 3, 15, 3, 4, 11, 14, 3};
	Simulation sim = Simulation();
	double out = sim.run(in);
	assert(out == 1e100);
	// std::cout << out << std::endl;
}

void test_my_queue10()
{
	std::vector<int> in = {6, 5, 5, 5, 3, 6, 2, 2, 10, 4, 2, 3, 4, 9, 0, 14, 10, 0, 8, 13, 5, 8, 5, 0, 0, 14, 3};
	Simulation sim = Simulation();
	double out = sim.run(in);
	assert(out == 1e100);
	// std::cout << out << std::endl;
}

void test_my_queue11()
{
	std::vector<int> in = {6, 0, 6, 2, 0, 1, 6, 1, 0, 6, 6, 2, 2, 0, 6, 5, 1, 1, 0, 5, 2, 6, 1, 6, 2, 1, 5, 0, 1, 6, 1, 1, 1, 6, 0, 7, 12, 14, 4, 0, 6, 12, 6, 1, 13, 2, 12, 1, 12, 13, 13, 7, 7, 11, 16};
	Simulation sim = Simulation();
	double out = sim.run(in);
	assert(out == 1e100);
	// std::cout << out << std::endl;
}

void test_my_queue12()
{
	std::vector<int> in = {0,2,6,2,1,5,6,2,6,9,1,0,6,4,6,0,1,6,1,1,14,6,5,1,13,1,6,0,13,1,1,0,6,6,5,0,12,12,12,8,13,2,12,2,11,0,0,6,2,6,2,2,7,7,7,7,3,16};
	Simulation sim = Simulation();
	double out = sim.run(in);
	assert(out == 1e100);
	// std::cout << out << std::endl;
}

void test_my_queue13()
{
	std::vector<int> in = {5, 1, 1, 6, 6, 1, 5, 6, 3, 4, 6, 3, 6, 6, 0, 6, 6, 2, 6};
	Simulation sim = Simulation();
	double out = sim.run(in);
	//assert(out == 1e100);
	// std::cout << out << std::endl;
}

void test_my_queue14()
{
	std::vector<int> in = {3, 0, 0, 6, 4, 4, 2, 4, 1, 6, 1, 3, 5, 0, 8, 9, 14, 1, 8, 8, 13, 9, 3, 9, 9, 14, 12, 8, 4, 13, 4, 13, 8, 4, 14, 14, 3, 4, 10, 13, 10, 12, 15, 15, 4, 9, 6, 15, 0, 10, 8, 6, 1, 1, 1, 15, 12, 1, 15, 13, 1, 9, 8, 12, 6, 4, 1, 2, 6, 10, 15, 2, 4, 2, 16, 6, 5, 9, 14, 12, 0, 10, 15, 0, 8, 6, 11, 15, 15, 6, 11, 12, 3, 1, 16, 5, 1, 16, 12, 15, 14, 10, 4, 5, 16, 16, 4, 14, 6, 10, 9, 12, 0, 15, 5, 11, 8, 3, 16, 10};
	Simulation sim = Simulation();
	double out = sim.run(in);
	// assert(out == 1e100);
	// std::cout << out << std::endl;
}

void test_my_queue15()
{
	std::vector<int> in = {6,0,0,6,0,0,6,1,0,6,1,0,6,1,1,6,2,1,6,2,1,6,2,1,9,2,6,1,2,6,2,1,9,4,6,2,1,8,14,8,8,12,10,13,13,10,12,12,12,13,10,11,10,16 };
	Simulation sim = Simulation();
	double out = sim.run(in); // 758237
	assert(out < 758238 && out > 758236); // 210.621
}

void test_my_queue16()
{
	std::vector<int> in = {6,0,0,6,0,0,6,1,0,6,1,0,6,1,1,6,2,8,1,6,2,1,6,2,1,9,2,6,1,2,6,2,1,9,4,6,2,1,8,14,8,12,10,13,13,10,12,12,12,13,10,11,10,16};
	Planet planet = Planet();
	for (int s: in){
		planet.upgrade_structure(s);
	}
	planet.finish_queues();
	
	// std::cout << planet.getTime()/3600 << " " << planet.getResources() << " " <<planet.getPlanetExtraction() << std::endl;
}

void test_my_queue17()
{
	std::vector<int> in = {0, 0, 0, 0, 0, 6,6,6,6,6, 1,1,1,1,1, 2,2,2,2,2,6,6,6,8,14,0};
	Planet planet = Planet();
	for (int s: in){
		int status = planet.upgrade_structure(s);
		if (status != 0)
		{
			std::cout <<"error in status: " << status << std::endl;
			break;
		}
	}
	planet.finish_queues();
	
	std::cout << planet.getTime() << " " << planet.getResources() << " " <<planet.getPlanetExtraction() << std::endl;
}

void test_my_queue18()
{
	std::vector<int> in = {1, 6, 1, 6, 0, 0, 0, 3, 0, 3, 1, 2, 2, 3, 3, 2, 2, 4, 6, 4, 9, 8, 14, 0, 3, 8, 6, 5, 14, 13, 14, 5, 1, 1, 1, 6, 3, 2, 7, 9, 9, 5, 3, 5, 2, 4, 9, 7, 7, 1, 5, 14, 3, 5, 0, 5, 10, 13, 6, 6, 2, 9, 10, 15, 8, 3, 6, 7, 9, 13, 10, 4, 4, 13, 15, 12, 15, 3, 5, 3, 12, 2, 12, 2, 4, 8, 1, 4, 8, 9, 5, 6, 2, 2, 1, 2, 10, 6, 14, 6, 12, 16, 9, 13, 3, 6, 7, 10, 0, 14, 2, 1, 0, 10, 2, 14, 16, 11, 13, 14, 4, 8, 14, 2, 8, 9, 0, 5, 6, 16, 0, 3, 2, 5, 12, 15, 10, 11, 3, 9, 15, 2, 13, 3, 12, 12, 4, 13, 13, 12, 4, 3, 6, 16, 11, 9, 6, 12, 15, 8, 16, 5, 3, 0, 9, 9, 15, 7, 9, 11, 3, 6, 2, 7, 2, 15, 13, 3, 9, 2, 11, 7, 1, 11, 0, 3, 16, 15, 16, 4, 14, 14, 14, 15, 14, 15, 4, 14, 14, 15};
	Planet planet = Planet();
	for (int s: in){
		int status = planet.upgrade_structure(s);
		if (status != 0)
		{
			std::cout <<"error in status: " << status << std::endl;
			break;
		}
	}
	planet.finish_queues();
	
	std::cout << planet.getTime() << " " << planet.getResources() << " " <<planet.getPlanetExtraction() << std::endl;
	
}

void test_my_queue19()
{
	//193.888
	std::vector<int> in = {6,0,0,6,0,0,6,0,6,1,1,0,6,1,1,6,0,1,0,6,1,6,0,1,6,2,2,2,6,1,2,9,6,2,4,2,1,6,1,2,1,9,10,15,6,1,2,8,8,10,14,8,12,12,12,13,13,10,13,10,3,3,3,12,11,16};
	Simulation sim = Simulation();
	double out = sim.run(in); // 697996
	// assert(out < 697996 && out > 697996);
}

void test_my_queue20()
{
	//193.942
	std::vector<int> in = {6,0,0,6,0,0,6,0,6,1,1,0,6,1,1,6,0,1,0,6,1,0,6,1,6,1,2,6,2,2,2,9,6,1,2,9,10,2,15,2,6,1,1,4,6,1,2,8,8,8,12,12,14,10,13,13,12,12,13,10,3,3,10,11,3,16};
	Simulation sim = Simulation();
	double out = sim.run(in); // 697996
	// assert(out < 697996 && out > 697996);
}

void test_my_queue21()
{
	//193.825
	std::vector<int> in = {6,0,0,6,0,0,6,0,6,1,1,1,6,0,0,6,1,1,0,6,0,6,1,1,6,1,2,2,6,2,2,9,6,2,1,2,6,1,1,4,9,10,2,15,6,8,2,14,8,1,13,13,10,8,12,12,12,12,13,3,10,3,10,11,16};
	Simulation sim = Simulation();
	double out = sim.run(in); // 697996
	std::cout << "final outcoume: "<< out << " " << out /3600 << std::endl;
	// assert(out < 697996 && out > 697996);
}

void test_my_queue22()
{
// 	Elektrownia słoneczna (Poziom 1)
// Kopalnia metalu (Poziom 1)
// Kopalnia metalu (Poziom 2)
// Elektrownia słoneczna (Poziom 2)
// Kopalnia metalu (Poziom 3)
// Kopalnia metalu (Poziom 4)
// Elektrownia słoneczna (Poziom 3)
// Kopalnia metalu (Poziom 5)
// Kopalnia kryształu (Poziom 1)
// Kopalnia kryształu (Poziom 2)
// Kopalnia kryształu (Poziom 3)
// Elektrownia słoneczna (Poziom 4)
// Kopalnia kryształu (Poziom 4) 
// Elektrownia słoneczna (Poziom 5) --
// Kopalnia metalu (Poziom 6)
// Elektrownia słoneczna (Poziom 6)
// Kopalnia kryształu (Poziom 5)
// Kopalnia kryształu (Poziom 6)
// Ekstraktor deuteru (Poziom 1)
// Elektrownia słoneczna (Poziom 7)
// Ekstraktor deuteru (Poziom 2)
// Ekstraktor deuteru (Poziom 3)
// Elektrownia słoneczna (Poziom 8)
// Ekstraktor deuteru (Poziom 4)
// Ekstraktor deuteru (Poziom 5)
// Ekstraktor deuteru (Poziom 6)
// Elektrownia słoneczna (Poziom 9) ---
// Fabryka robotów (Poziom 1)
// Fabryka robotów (Poziom 2)
// Laboratorium badawcze (Poziom 1)
// Technologia energetyczna (Poziom 1)
// Napęd spalinowy (Poziom 1)
// Napęd spalinowy (Poziom 2)
// Stocznia orbitalna (Poziom 1)
// Stocznia orbitalna (Poziom 2)
// Mały transporter
						   //0,6,0,6,0,0,6,0,6,1,1,0,1,6,2,6,1,2,6,2,1,2,6,2,9,2,3,8,15,13,9,13,10,10,18
	// std::vector<int> in = {6,0,0,6,0,0,6,0,1,1,1,6,1,6,0,6,1,1,2,6,2,2,6,2,2,2,6,9,9,8,15,13,13,10,10,18};
	std::vector<int> in = {0,6,6,0,0,0,6,0,6,1,2,1,6,1,2,6,2,2,6,1,2,6,8,1,9,15,13,13,9,10,10,18};
	Simulation sim = Simulation();
	double out = sim.run(in); // 697996
	std::cout << "final outcoume: "<< out << " " << out /3600 << std::endl;
	// assert(out < 697996 && out > 697996);
}
//0 6 6 0 0 0 6 0 6 1 2 1 6 1 2 6 2 2 6 1 2 6 8 1 9 15 13 13 9 10 10 18 // 53.2491

void run_ogame()
{
	// test_mines_cost();
	// test_upgrade_time();
	// test_upgrade();
	// test_queues();
	// test_robot_factory_speedup();
	// test_robot_factory_not_affecting_others();
	// test_my_queue2();
	// test_my_queue3();
	// test_my_queue4();
	// test_my_queue5();
	// test_my_queue6();
	// test_my_queue7();
	// test_my_queue8();
	// test_my_queue9();
	// test_my_queue10();
	// test_my_queue11();
	// test_my_queue12();
	// test_my_queue13();
	// test_my_queue14();
	// test_my_queue15();
	// test_my_queue16();
	// test_my_queue17();
	// test_my_queue18();
	// test_my_queue19();
	// test_my_queue20();
	// test_my_queue21();
	test_my_queue22();
}

