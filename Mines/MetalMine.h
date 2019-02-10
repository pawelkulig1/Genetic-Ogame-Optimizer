//
// Created by Paweł Kulig on 2019-02-07.
//

#ifndef OGAME_METALMINE_H
#define OGAME_METALMINE_H


#include "Mine.h"

class MetalMine : public Mine {
public:
    MetalMine(const Resources &defaultCost = Resources(60, 15, 0, 0),
              const double costRatio = 1.5,
              const Resources &defaultProductionPerHour = Resources(30, 0, 0, 0),
              double productionRatio = 30,
              double energyRatio = 10);
};


#endif //OGAME_METALMINE_H
