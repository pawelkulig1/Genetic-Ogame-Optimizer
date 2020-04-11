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
    SolarPlant(Resources defaultCost = Resources(75, 30, 0, 0),
               double costRatio = 1.5, int productionRatio = 20);

    Resources getProductionPerHour() const;
};


#endif //OGAME_SOLARPLANT_H
