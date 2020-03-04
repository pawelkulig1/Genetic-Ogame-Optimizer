//
// Created by Paweł Kulig on 2019-01-12.
//

#ifndef OGAME_MINE_H
#define OGAME_MINE_H


#include "../Resources.h"
#include "../Building.h"

class Mine : public Building {
protected:

    Resources defaultProductionPerHour;
public:
    virtual const Resources &getDefaultProductionPerHour() const;

protected:
    double productionRatio;
    double energyRatio;
public:
    Mine(const Resources &defaultCost, const double costRatio, const Resources &defaultProductionPerHour,
         double productionRatio, double energyRatio);

    virtual const Resources getProductionPerHour() const = 0;

    virtual Resources getEnergyConsumption();


};


#endif //OGAME_MINE_H
