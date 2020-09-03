#include "DeuteriumStorage.h"

DeuteriumStorage::DeuteriumStorage(const Resources& defaultCost): Building(defaultCost)
{

}

Resources DeuteriumStorage::getStorageCapacity() const
{
    if (lvl > max_level) {
        return Resources(0, 0, m_capacity[max_level]);
    }
    return Resources(0, 0, m_capacity[lvl]);
}