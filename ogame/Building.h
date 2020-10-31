//
// Created by Paweł Kulig on 2019-01-12.
//

#ifndef OGAME_BUILDING_H
#define OGAME_BUILDING_H


#include "structure.h"
#include <array>
#include <math.h>

static consteval std::array<double, 40> get_cache_ratio()
{
    std::array<double, 40> temp;
    for(int i = 0; i < 40; i++)
    {
        temp[i] = pow(1.1, i);
    }
    return temp;
}


class Building : public Structure{
public:
	virtual ~Building();
    Building(Resources default_cost, double cost_ratio = 2);
    constexpr static std::array<double, 40> cache_ratio = get_cache_ratio();

};


#endif //OGAME_BUILDING_H
