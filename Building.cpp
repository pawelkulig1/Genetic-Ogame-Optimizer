//
// Created by Paweł Kulig on 2019-01-12.
//

#include <cmath>
#include "Building.h"

int Building::getLvl() const {
    return lvl;
}

const Resources &Building::getDefaultCost() const {
    return defaultCost;
}

const double Building::getCostRatio() const {
    return costRatio;
}

void Building::setLvl(int lvl) {
    Building::lvl = lvl;
}

Resources Building::getNextLevelCost() const {
    return defaultCost * pow(costRatio, (lvl));
}

void Building::operator++() {
    this->lvl++;
}

double Building::getConstructionTime() {
    Resources nlc = getNextLevelCost();
    constructionTimeSec = 3600 * (nlc.at(0) + nlc.at(1)) / (2500 * (PoziomFabrRobot + 1)) * pow(0.5, PoziomFabNanit);
    return constructionTimeSec;
}

Building::Building(const Resources &defaultCost, const double costRatio) : defaultCost(defaultCost),
                                                                           costRatio(costRatio) {}

const std::string &Building::getName() const {
    return name;
}

void Building::setName(const std::string &name) {
    Building::name = name;
}

std::ostream &operator<<(std::ostream &out, const Building &b) {
    out << "Name: " << b.name << ", ";
    out << "lvl: " << b.lvl;
    return out;
}