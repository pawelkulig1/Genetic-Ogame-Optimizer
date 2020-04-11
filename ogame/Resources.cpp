//
// Created by Paweł Kulig on 2019-01-12.
//

#include <string>
#include "Resources.h"
#include <math.h>
#include <sstream>

Resources::Resources(data_type metal, data_type crystal, data_type deuterium) :
        metal(metal), crystal(crystal), deuterium(deuterium) {}

Resources::Resources() : metal(0), crystal(0), deuterium(0) {}

Resources::Resources(data_type metal, data_type crystal) : metal(metal), crystal(crystal) {}

Resources::Resources(data_type metal, data_type crystal, data_type deuterium, data_type energy) :
        metal(metal), crystal(crystal), deuterium(deuterium), energy(energy) {}

Resources::data_type Resources::getMetal(void) const{
    return metal;
}

Resources::data_type Resources::getCrystal(void) const {
    return crystal;
}

Resources::data_type Resources::getDeuterium() const {
    return deuterium;
}

Resources::data_type Resources::at(int n) const {
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
	//throw
	return -1;
}

void Resources::setMetal(data_type metal) {
    this->metal = metal;
}

void Resources::setCrystal(data_type crystal) {
    this->crystal = crystal;
}

void Resources::setDeuterium(data_type deuterium) {
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

Resources::data_type Resources::getEnergy() const {
    return energy;
}

void Resources::setEnergy(data_type energy) {
    Resources::energy = energy;
}

Resources Resources::operator*(data_type mult) {
    Resources temp;
    temp.setMetal(metal * mult);
    temp.setCrystal(crystal * mult);
    temp.setDeuterium(deuterium * mult);
    temp.setEnergy(energy * mult);
    return temp;
}

Resources Resources::operator^(data_type exponent) {
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

bool Resources::operator>(Resources required) {
	return (metal > required.metal &&
			crystal > required.crystal &&
			deuterium > required.deuterium);
}

bool Resources::operator>(data_type required)
{
	return (metal > required &&
			crystal > required &&
			deuterium > required);
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

Resources Resources::operator/(data_type divider) {
    return Resources(
            metal / divider,
            crystal / divider,
            deuterium / divider,
            energy
    );
}

Resources Resources::operator*(data_type mult) const {
    Resources temp;
    temp.setMetal(metal * mult);
    temp.setCrystal(crystal * mult);
    temp.setDeuterium(deuterium * mult);
    //temp.setEnergy(energy * mult);
    return temp;
}




