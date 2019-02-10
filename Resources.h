//
// Created by Paweł Kulig on 2019-01-12.
//

#ifndef OGAME_RESOURCES_H
#define OGAME_RESOURCES_H

#include <iostream>

#pragma once

class Resources {
    double metal;
    double crystal;
    double deuterium;
    double energy;
public:
    double getEnergy() const;

    void setEnergy(double energy);

public:
    Resources();

    Resources(double, double);

    Resources(double, double, double);

    Resources(double, double, double, double);

    double getMetal(void);

    double getCrystal(void);

    double getDeuterium();

    double at(int n);

    void setMetal(double);

    void setCrystal(double);

    void setDeuterium(double);

    Resources operator+(Resources);

    Resources operator-(Resources);

    Resources operator*(double);

    Resources operator^(double);

    Resources operator/(double);

    Resources operator*(double) const;

    bool operator>=(Resources);

    friend std::ostream &operator<<(std::ostream &stream, const Resources &resources);
};


#endif //OGAME_RESOURCES_H
