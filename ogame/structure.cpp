#include "structure.h"
#include <cmath>

Structure::~Structure()
{
	lvl = 0;
}

int Structure::getLvl() const {
    return lvl;
}

const Resources &Structure::getDefaultCost() const {
    return defaultCost;
}

const double Structure::getCostRatio() const {
    return costRatio;
}

void Structure::setLvl(int lvl) {
    Structure::lvl = lvl;
}

Resources Structure::getNextLevelCost() const {
    return defaultCost * pow(costRatio, (lvl));
}

void Structure::operator++() {
    this->lvl++;
}

double Structure::getConstructionTime(int robot_factory_level, int nanite_factory_level) {
    Resources nlc = getNextLevelCost();
    return (3600 * (nlc.at(0) + nlc.at(1)) / (2500 * (robot_factory_level+ 1)) * pow(0.5, nanite_factory_level));
}

Structure::Structure(const Resources &defaultCost, const double costRatio) : defaultCost(defaultCost),
                                                                           costRatio(costRatio) {}

std::string Structure::getName() const {
    return name;
}

void Structure::setName(std::string name) {
    Structure::name = name;
}

std::ostream &operator<<(std::ostream &out, const Structure &b) {
    out << "Name: " << b.name << ", ";
    out << "lvl: " << b.lvl;
    return out;
}
