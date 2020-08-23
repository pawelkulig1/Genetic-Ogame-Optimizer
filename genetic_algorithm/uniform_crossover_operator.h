#pragma once
#include "crossover.h"
#include <vector>

template <class T>
class UniformCrossoverOperator: public Crossover<T> {
    std::vector<T> cross(const T &parent1, const T &parent2) override final;
    
};

template <class T>
std::vector<T> UniformCrossoverOperator<T>::cross(const std::vector<T> &parent1, const std::vector<T> &parent2) 
{
    const int_fast32_t min_size = std::min(parent1.size(), parent2.size()) - 1;

    Chromosome child = Chromosome();
    child.reserve(min_size);
    RandomGenerators *rnd = RandomGenerators::get_instance();
    int i = 0;
    for (;i<min_size;i++)
    {
        if (rnd->get_random_int(0, 1) != 0)
            child.append_gene(parent2.get(i));
        else
        {
            child.append_gene(parent1.get(i));
        }
    }
    return child;

}