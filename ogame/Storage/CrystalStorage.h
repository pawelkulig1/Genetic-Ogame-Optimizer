#pragma once

#include "Building.h"
#include "common_includes.h"
#include <array>

class CrystalStorage: public Building
{
    static constexpr int max_level = 20;
    std::array<globals::type, 20> m_capacity = {
        10      *   1e3,
        20      *   1e3,
        40      *   1e3,
        75      *   1e3,
        140     *   1e3,
        255     *   1e3,
        470     *   1e3,
        865     *   1e3,
        1.59    *   1e6,
        2.92    *   1e6,
        5.355   *   1e6,
        9.82    *   1e6,
        18.005  *   1e6,
        33.005  *   1e6,
        60.510  *   1e6,
        110.925 *   1e6,
        203.350 *   1e6,
        372.785 *   1e6,
        683.385 *   1e6,
        1252.785*   1e6
        //2296.600*   1e6,

    };

public:
    CrystalStorage(const Resources& defaultCost = Resources(0, 1000, 0, 0));

    Resources getStorageCapacity() const;
};
