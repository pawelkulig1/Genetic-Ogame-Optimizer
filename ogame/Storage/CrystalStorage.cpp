#include "CrystalStorage.h"

CrystalStorage::CrystalStorage(const Resources& defaultCost): Building(defaultCost)
{

}

Resources CrystalStorage::getStorageCapacity() const
{
    if (lvl > max_level) {
        throw(std::runtime_error("Crystal Storage max level is 20!"));
    }
    return Resources(0, m_capacity[lvl], 0);
}