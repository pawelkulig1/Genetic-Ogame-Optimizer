#pragma once
#include "crossover.h"
#include <vector>
#include <cstdint>
#include "random_generators.h"

template <class T>
class BasicCrossoverOperator : public Crossover<T>
{
public:
    std::vector<T> cross(const std::vector<T> &parent1, const std::vector<T> &parent2) override final
    {
        const int_fast32_t min_size = std::min(parent1.size(), parent2.size()) - 1;
        const int_fast32_t max_size = std::max(parent1.size(), parent2.size()) - 1;
        if (min_size <= 2)
        {
            return parent1;
        }
        RandomGenerators *rnd = RandomGenerators::get_instance();
        const int_fast32_t pivot1 = rnd->get_random_int(0, min_size - 1);

        std::vector<T> child;
        child.reserve(max_size);
        child.insert(child.begin(), parent1.begin(), parent1.begin() + pivot1);
        child.insert(child.end(), parent2.begin() + pivot1, parent2.end());
        return child;
    }
};
