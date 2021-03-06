#include "chromosome.h"
#include <stdexcept>
#include <iostream>

void Chromosome::append_gene(chromosome_type gene)
{
    push_back(gene);
}

void Chromosome::insert_gene(chromosome_type gene, int index)
{
    if (size() <= index)
    {
        throw std::invalid_argument("Chromosome::insert_gene: index out of range");
    }
    insert(begin() + index, gene);
}

// void Chromosome::replace_gene(Chromosome::chromosome_type gene, int index)
// {	
//     if (m_chromosome.size() <= index)
//     {
//         throw std::invalid_argument("Chromosome::insert_gene: index out of range");
//     }

//     m_chromosome.at(index) = gene;
// }

// Chromosome::chromosome_type Chromosome::get(int index) const
// {
//     if (m_chromosome.size() <= index || index < 0)
//     {
//         throw std::invalid_argument("Chromosome::get: index out of range");
//     }
//     return m_chromosome[index];
// }
// const std::vector<Chromosome::chromosome_type> &Chromosome::get_vector() const
// {
//     return m_chromosome;
// }

// void Chromosome::set_chromosome(Chromosome::data_store &vec)
// {
//     clear();
//     m_chromosome = vec;
// }

// void Chromosome::set_chromosome(int pos, Chromosome::data_store::const_iterator beg, Chromosome::data_store::const_iterator end)
// {
//     m_chromosome.insert(m_chromosome.begin() + pos, beg, end);
// }

// void Chromosome::reserve(size_t size)
// {
//     m_chromosome.reserve(size);
// }

// void Chromosome::swap(int pos1, int pos2)
// {
//     auto temp = m_chromosome.at(pos1);
//     m_chromosome.at(pos1) = m_chromosome.at(pos2);
//     m_chromosome.at(pos2) = temp;
// }

// int Chromosome::has(chromosome_type obj)
// {
// 	for (int i=0;i<m_chromosome.size();i++)
// 	{
// 		if (m_chromosome.at(i) == obj) return i;
// 	}
// 	return -1;
// }

// Chromosome::data_store::const_iterator Chromosome::begin() const
// {
//     return m_chromosome.begin();
// }

// Chromosome::data_store::const_iterator Chromosome::end() const
// {
//     return m_chromosome.end();
// }

// void Chromosome::remove_from(int index) 
// {
//     m_chromosome = data_store(m_chromosome.begin(), m_chromosome.begin() + index);
// }

// void Chromosome::remove(int index)
// {
//     m_chromosome.erase(m_chromosome.begin() + index, m_chromosome.begin() + index + 1);
// }

std::ostream &operator<<(std::ostream &out, const Chromosome &chromosome)
{
    for (int i=0;i<chromosome.m_chromosome.size();++i)
    {
        out << chromosome.m_chromosome.at(i) << " ";
    }

    return out;
}
