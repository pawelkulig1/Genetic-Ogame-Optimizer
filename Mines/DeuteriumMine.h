//
// Created by Paweł Kulig on 2019-02-08.
//

#ifndef OGAME_DEUTERIUMMINE_H
#define OGAME_DEUTERIUMMINE_H


#include "Mine.h"

class DeuteriumMine : public Mine {
public:
    DeuteriumMine(const Resources &defaultCost = Resources(225, 75, 0, 0),
                  const double costRatio = 1.5,
                  const Resources &defaultProductionPerHour = Resources(0, 0, 0, 0),
                  double productionRatio = 10,
                  double energyRatio = 20);

    Resources getProductionPerHour() override;
};


#endif //OGAME_DEUTERIUMMINE_H
