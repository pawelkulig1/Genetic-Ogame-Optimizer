#include "DeuteriumStorage.h"

DeuteriumStorage::DeuteriumStorage(const Resources& defaultCost): Building(defaultCost)
{

}

Resources DeuteriumStorage::getStorageCapacity() const
{
    if (lvl > max_level) {
        throw(std::runtime_error("Deuterium Storage max level is 20!"));
    }
    return Resources(0, 0, m_capacity[lvl]);
}