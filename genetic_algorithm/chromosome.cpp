#include "chromosome.h"
#include <stdexcept>
#include <iostream>

void Chromosome::append_gene(Chromosome::chromosome_type gene)
{
	m_chromosome.push_back(gene);
}

void Chromosome::insert_gene(Chromosome::chromosome_type gene, int index)
{
	if (m_chromosome.size() <= index)
	{
		throw std::invalid_argument("Chromosome::insert_gene: index out of range");
	}
	m_chromosome.insert(m_chromosome.begin() + index, gene);
}

void Chromosome::replace_gene(Chromosome::chromosome_type gene, int index)
{	
	if (m_chromosome.size() <= index)
	{
		throw std::invalid_argument("Chromosome::insert_gene: index out of range");
	}

	m_chromosome.at(index) = gene;
}

Chromosome::chromosome_type Chromosome::get(int index) const
{
	if (m_chromosome.size() <= index || index < 0)
	{
		throw std::invalid_argument("Chromosome::get: index out of range");
	}
	return m_chromosome[index];
}
const std::vector<Chromosome::chromosome_type> &Chromosome::get_vector() const
{
	return m_chromosome;
}

void Chromosome::set_chromosome(Chromosome::data_store &vec)
{
	m_chromosome.clear();
	m_chromosome = vec;
}

void Chromosome::set_chromosome(int pos, Chromosome::data_store::const_iterator beg, Chromosome::data_store::const_iterator end)
{
	m_chromosome.insert(m_chromosome.begin() + pos, beg, end);
}

void Chromosome::reserve(size_t size)
{
	m_chromosome.reserve(size);
}

Chromosome::data_store::const_iterator Chromosome::begin() const
{
	return m_chromosome.begin();
}

Chromosome::data_store::const_iterator Chromosome::end() const
{
	return m_chromosome.end();
}

std::ostream &operator<<(std::ostream &out, const Chromosome &chromosome)
{
	for (int i=0;i<chromosome.m_chromosome.size();++i)
	{
		out << chromosome.m_chromosome.at(i) << " ";
	}

	return out;
}
