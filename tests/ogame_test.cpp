#include <assert.h>
#include "MetalMine.h"
#include "SolarPlant.h"
#include "CrystalMine.h"
#include "DeuteriumMine.h"
#include "Simulation.h"
#include <cassert>
#include <chrono>

using namespace globals;
constexpr int M = static_cast<int>(Upgradables::METAL_MINE);
constexpr int C = static_cast<int>(Upgradables::CRYSTAL_MINE);
constexpr int D = static_cast<int>(Upgradables::DEUTERIUM_MINE);
constexpr int S = static_cast<int>(Upgradables::SOLAR_PLANT);
constexpr int MS = static_cast<int>(Upgradables::METAL_STORAGE);
constexpr int DS = static_cast<int>(Upgradables::DEUTERIUM_STORAGE);
constexpr int CS = static_cast<int>(Upgradables::CRYSTAL_STORAGE);
constexpr int L = static_cast<int>(Upgradables::LABORATORY);
constexpr int R = static_cast<int>(Upgradables::ROBOT_FACTORY);
constexpr int SH = static_cast<int>(Upgradables::SHIPYARD);
constexpr int SS = static_cast<int>(Upgradables::SOLAR_SATELLITE);
constexpr int ID = static_cast<int>(Upgradables::IMPULSE_DRIVE);
constexpr int AT = static_cast<int>(Upgradables::ARMOUR_TECHNOLOGY);
constexpr int AP = static_cast<int>(Upgradables::ASTROPHYSICS);

static const std::vector<double> sim_err{0, 0, 0};

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
	constexpr int espionage_techonology = static_cast<int>(globals::Upgradables::ESPIONAGE_TECHNOLOGY);
	constexpr int solar_satellite = static_cast<int>(globals::Upgradables::SOLAR_SATELLITE);
	std::vector<int> in = {0, 6, 6, 0, 2, 2, 8, 10};
	Planet planet = Planet();
	for (int s: in){
		planet.upgrade_structure(s);
	}
	planet.finish_queues();
	double first_l = planet.get_construction_time(espionage_techonology);
	double first_s = planet.get_construction_time(solar_satellite);
	planet.upgrade_structure(9);
	planet.finish_queues();
	double second_l = planet.get_construction_time(espionage_techonology);
	double second_s = planet.get_construction_time(solar_satellite);
	assert(second_l == first_l);
	assert(second_s == first_s);
}

std::vector<int> stable_baseline()
{
	std::vector<int> in;
	for(int i = 0;i < 6; i++)
	{
		in.push_back(S);
		in.push_back(M);
		in.push_back(M);
		if (i % 2 == 0)
			in.push_back(MS);
	}
	for(int i = 0;i < 5; i++)
	{
		in.push_back(S);
		in.push_back(C);
		in.push_back(C);
		if (i % 2 == 0)
			in.push_back(CS);
	}

	for(int i = 0;i < 5; i++)
	{
		in.push_back(S);
		in.push_back(D);
		in.push_back(D);
	}
	in.push_back(DS);
	in.push_back(L);
	in.push_back(L);
	in.push_back(L);
	in.push_back(R);
	in.push_back(R);
	in.push_back(SH);
	return in;
}

void test_simultaneous_queues()
{
	std::vector<int> in = stable_baseline();
	std::vector<int> another{M, M, SS};
	in.insert(in.end(), another.begin(), another.end());
	Planet p = Planet();
	for(const int x: in)
	{
		p.upgrade_structure(x);
	}
	assert(p.getQueues().isEmpty(0) == false);
	assert(p.getQueues().isEmpty(1) == true);
	assert(p.getQueues().isEmpty(2) == false);

	in = stable_baseline();
	another = {M, M, SS, AT};
	in.insert(in.end(), another.begin(), another.end());
	Planet p2 = Planet();
	for(const int x: in)
	{
		p2.upgrade_structure(x);
	}
	assert(p2.getQueues().isEmpty(0) == false);
	assert(p2.getQueues().isEmpty(1) == false);
	assert(p2.getQueues().isEmpty(2) == false);
}

void test_two_planets()
{
	std::vector<int> in_1 = {0, 6};
	std::vector<int> in_2 = {1, 6};
	std::vector<Planet> planets;
	planets.push_back(Planet());
	planets.push_back(Planet());
	for (int s: in_1){
		int status = planets[0].upgrade_structure(s);

		if (status != 0)
		{
			std::cout <<"error in status: " << status << std::endl;
			break;
		}
	}
	for (int s: in_2){
		int status = planets[1].upgrade_structure(s);

		if (status != 0)
		{
			std::cout <<"error in status: " << status << std::endl;
			break;
		}
	}
	planets[0].finish_queues();
	planets[1].finish_queues();

	int p2 = static_cast<int>(globals::Upgradables::SIZE);
	std::vector<int> in = {M, p2+C, S, p2+S};
	Simulation sim = Simulation();
	auto out = sim.run(in);

	assert(std::max(planets[0].getTime(), planets[1].getTime()) == out[0]);
	assert(planets[0].getPoints() + planets[1].getPoints() == out[1]);
	assert(planets[0].getLoadedResources() + planets[1].getLoadedResources() ==  out[2]);

}

void test_only_ship()
{
	std::vector<int> in = {SS};
	Simulation sim = Simulation();
	assert(sim.run(in) == sim_err);
}

void test_planet_creation_time()
{
	std::vector<Planet> vec;
	auto start = std::chrono::steady_clock::now();
	for(int i{0}; i< 2 * 50 * 100;i++) {vec.emplace_back(Planet());}
	// std::fill_n(vec.begin(), 100, Planet());
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> delta = end - start;
	std::cout << "time: " << delta.count() << '\n';
}

void run_ogame()
{
	test_two_planets();
	test_mines_cost();
	test_upgrade_time();
	test_robot_factory_speedup();
	test_robot_factory_not_affecting_others();
	test_simultaneous_queues();
	test_only_ship();

	test_planet_creation_time();

}
