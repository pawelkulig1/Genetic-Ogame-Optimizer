//
// Created by Paweł Kulig on 2019-02-07.
//

#ifndef OGAME_METALMINE_H
#define OGAME_METALMINE_H


#include "Mine.h"

class MetalMine : public Mine {
public:
    MetalMine(const Resources &defaultCost = Resources(60, 15, 0, 0.0),
              const double costRatio = 1.5,
              const Resources &defaultProductionPerHour = Resources(30, 0, 0, 0),
              const int productionRatio = 30,
              const int energyRatio = 10);

    virtual ~MetalMine() {}

	const Resources getProductionPerHour() const override;
};


#endif //OGAME_METALMINE_H
