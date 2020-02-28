//
// Created by Paweł Kulig on 2019-01-12.
//

#ifndef OGAME_BUILDING_H
#define OGAME_BUILDING_H


#include "structure.h"


class Building : public Structure{
public:
	virtual ~Building();
    Building(Resources default_cost, double cost_ratio = 2);
};


#endif //OGAME_BUILDING_H
