#include "structure.h"
#include <cmath>
#include <cassert>

Structure::Structure(const Resources &defaultCost, const double costRatio):
					GameObject(defaultCost),
                    costRatio(costRatio)
{
	lvl = 0;
}

Structure::Structure(const Structure& structure) : GameObject(structure)
{
	lvl = structure.lvl;
	costRatio = structure.costRatio;
}

Structure::~Structure()
{
}

int Structure::getLvl() const {
    return lvl;
}

const double Structure::getCostRatio() const {
    return costRatio;
}

void Structure::setLvl(int lvl) {
    Structure::lvl = lvl;
}

Resources Structure::getUpgradeCost() const {
	assert(costRatio > 0.0);
    return defaultCost * pow(costRatio, (lvl));
}

void Structure::operator++() {
    this->lvl++;
}

double Structure::getConstructionTime(int robot_factory_level, int nanite_factory_level) const {
    Resources nlc = getUpgradeCost();
    return (3600 * (nlc.at(0) + nlc.at(1)) / (2500 * (robot_factory_level + 1)) * nanite_cache[nanite_factory_level]);
}
