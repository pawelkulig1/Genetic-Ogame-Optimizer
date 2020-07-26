#include "MetalStorage.h"

MetalStorage::MetalStorage(const Resources& defaultCost): Building(defaultCost)
{

}

Resources MetalStorage::getStorageCapacity() const
{
    if (lvl > max_level) {
        throw(std::runtime_error("Metal Storage max level is 20!"));
    }
    return Resources(m_capacity[lvl], 0, 0);
}