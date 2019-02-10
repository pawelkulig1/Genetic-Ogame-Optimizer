//
// Created by Paweł Kulig on 2019-02-08.
//

#ifndef OGAME_SOLARPLANT_H
#define OGAME_SOLARPLANT_H


#include "Building.h"

class SolarPlant : public Building {
private:
    int productionRatio;
public:
    SolarPlant(const Resources &defaultCost = Resources(75, 30, 0, 0),
               const double costRatio = 1.5, int productionRatio = 20);

    Resources getProductionPerHour();
};


#endif //OGAME_SOLARPLANT_H
