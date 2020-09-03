#include "MetalStorage.h"

MetalStorage::MetalStorage(const Resources& defaultCost): Building(defaultCost)
{

}

Resources MetalStorage::getStorageCapacity() const
{
    if (lvl > max_level) {
        return Resources(m_capacity[max_level], 0, 0);
    }
    return Resources(m_capacity[lvl], 0, 0);
}