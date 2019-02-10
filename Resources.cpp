//
// Created by Paweł Kulig on 2019-01-12.
//

#include <string>
#include "Resources.h"
#include <math.h>
#include <sstream>

Resources::Resources(double metal, double crystal, double deuterium) :
        metal(metal), crystal(crystal), deuterium(deuterium) {}

Resources::Resources() : metal(0), crystal(0), deuterium(0) {}

Resources::Resources(double metal, double crystal) : metal(metal), crystal(crystal) {}

Resources::Resources(double metal, double crystal, double deuterium, double energy) :
        metal(metal), crystal(crystal), deuterium(deuterium), energy(energy) {}


double Resources::getMetal(void) {
    return metal;
}

double Resources::getCrystal(void) {
    return crystal;
}

double Resources::getDeuterium() {
    return deuterium;
}

double Resources::at(int n) {
    if (n > 3 || n < 0)
        throw (std::string("Index out of bound!"));

    switch (n) {
        case 0:
            return metal;
        case 1:
            return crystal;
        case 2:
            return deuterium;
        case 3:
            return energy;
    }
}

void Resources::setMetal(double metal) {
    this->metal = metal;
}

void Resources::setCrystal(double crystal) {
    this->crystal = crystal;
}

void Resources::setDeuterium(double deuterium) {
    this->deuterium = deuterium;
}

Resources Resources::operator+(Resources recv) {
    Resources temp;
    temp.setMetal(metal + recv.metal);
    temp.setCrystal(crystal + recv.crystal);
    temp.setDeuterium(deuterium + recv.deuterium);
    temp.setEnergy(energy + recv.energy);
    return temp;
}

Resources Resources::operator-(Resources recv) {
    Resources temp;
    temp.setMetal(metal - recv.metal);
    temp.setCrystal(crystal - recv.crystal);
    temp.setDeuterium(deuterium - recv.deuterium);
    temp.setEnergy(energy - recv.energy);
    return temp;
}

double Resources::getEnergy() const {
    return energy;
}

void Resources::setEnergy(double energy) {
    Resources::energy = energy;
}

Resources Resources::operator*(double mult) {
    Resources temp;
    temp.setMetal(metal * mult);
    temp.setCrystal(crystal * mult);
    temp.setDeuterium(deuterium * mult);
    //temp.setEnergy(energy * mult);
    return temp;
}

Resources Resources::operator^(double exponent) {
    Resources temp;
    temp.setMetal(pow(metal, exponent));
    temp.setCrystal(pow(crystal, exponent));
    temp.setDeuterium(pow(deuterium, exponent));
    temp.setEnergy(pow(energy, exponent));
    return temp;
}

bool Resources::operator>=(Resources required) {
    return (metal >= required.metal &&
            crystal >= required.crystal &&
            deuterium >= required.deuterium);
}

std::ostream &operator<<(std::ostream &out, const Resources &resources) {
    std::ostringstream strs;
    strs << resources.metal;
    out << "Resources: [" + strs.str() + ", ";
    strs.str("");
    strs.clear();
    strs << resources.crystal;
    out << strs.str() + ", ";
    strs.str("");
    strs.clear();
    strs << resources.deuterium;
    out << strs.str() + ", ";
    strs.str("");
    strs.clear();
    strs << resources.energy;
    out << strs.str() + "]";
    strs.str("");
    strs.clear();

    return out;
}

Resources Resources::operator/(double divider) {
    return Resources(
            metal / divider,
            crystal / divider,
            deuterium / divider,
            energy
    );
}

Resources Resources::operator*(double mult) const {
    Resources temp;
    temp.setMetal(metal * mult);
    temp.setCrystal(crystal * mult);
    temp.setDeuterium(deuterium * mult);
    //temp.setEnergy(energy * mult);
    return temp;
}




