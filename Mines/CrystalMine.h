//
// Created by Paweł Kulig on 2019-02-08.
//

#ifndef OGAME_CRYSTALMINE_H
#define OGAME_CRYSTALMINE_H


#include "../Resources.h"
#include "Mine.h"

class CrystalMine : public Mine {
public:
    CrystalMine(const Resources &defaultCost = Resources(48, 24, 0, 0),
                const double costRatio = 1.6,
                const Resources &defaultProductionPerHour = Resources(0, 20, 0, 0),
                double productionRatio = 20,
                double energyRatio = 10);
};


#endif //OGAME_CRYSTALMINE_H
