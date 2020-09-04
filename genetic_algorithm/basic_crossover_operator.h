#pragma once
#include "crossover.h"
#include <vector>
#include <cstdint>
#include "random_generators.h"

template <class T>
class BasicCrossoverOperator : public Crossover<T>
{
public:
    std::pair<std::vector<T>, std::vector<T> > cross(const std::vector<T> &parent1, const std::vector<T> &parent2) override final
    {
        const uint_fast32_t min_size = std::min(parent1.size(), parent2.size()) - 1;
        const uint_fast32_t max_size = std::max(parent1.size(), parent2.size()) - 1;
        if (min_size <= 2)
        {
            return std::make_pair(parent1, parent2);
        }
        RandomGenerators *rnd = RandomGenerators::get_instance();
        const uint_fast32_t pivot = rnd->get_random_int(0, min_size - 1);

        std::vector<T> child1;
        std::vector<T> child2;
        child1.reserve(max_size);

        child1.insert(child1.begin(), parent1.begin(), parent1.begin() + pivot);
        child1.insert(child1.end(), parent2.begin() + pivot, parent2.end());

        child2.reserve(max_size);
        child2.insert(child2.begin(), parent2.begin(), parent2.begin() + pivot);
        child2.insert(child2.end(), parent1.begin() + pivot, parent1.end());
        return std::make_pair(child1, child2);
    }
};
