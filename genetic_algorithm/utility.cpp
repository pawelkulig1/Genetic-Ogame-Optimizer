#include "utility.h"
#include "common_includes.h"
#include "random_generators.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cassert>
#include <algorithm>

Chromosome Utility::generate_random_chromosome(int size)
{
	Chromosome ret = Chromosome();
	ret.reserve(size);
	RandomGenerators *rnd = RandomGenerators::get_instance();
	for (int i=0;i<size/1;i++)
	{
		ret.append_gene(rnd->get_random_int(0, 3));
	}

	for (int i=size/1;i<size;i++)
	{
		ret.append_gene(rnd->get_random_int(0, globals::Upgradables::SIZE-1));
	}
	
	return ret;
}

void Utility::prepare_initial_population()
{
	for (int i=0;i<m_population_size; ++i)
	{
		Chromosome chromosome = generate_random_chromosome(m_default_chromosome_size);
		double fitness = m_fitness_function(chromosome);
		m_chromosomes.push_back(std::make_pair(chromosome, fitness));
		//std::cout<<chromosome << " " << fitness << " " <<fitness / 3600 << "\n";
	}
	sort_chromosomes();
}

void Utility::sort_chromosomes()
{
	std::sort(m_chromosomes.begin(), m_chromosomes.end(), [](const std::pair<Chromosome, double> &p1, const std::pair<Chromosome, double> &p2)
			{ return p1.second > p2.second;});
}

void Utility::print()
{
	for (int i=0;i<m_population_size;++i)
	{
		std::cout<<m_chromosomes[i].first << " " << m_chromosomes[i].second << " " << (1 / m_chromosomes[i].second) / 3600 << " hours\n";
	}
}

void Utility::print_copy()
{
	std::cout << "m_chromosomes_copy.size(): " << m_chromosomes_copy.size() << std::endl;
	for (int i=0;i<m_chromosomes_copy.size();++i)
	{
		std::cout<<m_chromosomes_copy[i].first << " " << m_chromosomes_copy[i].second << " " << (1 / m_chromosomes_copy[i].second) / 3600 << "\n";	
	}

}

void Utility::drop_weak()
{
	if (drop_rate > 1 || drop_rate < 0)
	{
		std::runtime_error("Utility::drop_weak: drop_rate must be in range <0, 1>");
	}

	int count = (1 - drop_rate) * m_population_size;
	m_chromosomes.erase(m_chromosomes.begin() + count, m_chromosomes.end());
}

int Utility::select()
{
	double sum_of_fitness = 0;
	for (const std::pair<Chromosome, double> pair: m_chromosomes)
	{
		sum_of_fitness += pair.second;
	}
	double temp = 0;
	
	double pos = RandomGenerators::get_instance()->get_random_double(0, sum_of_fitness); 
	for(int i=0; i< m_chromosomes.size();i++)
	{
		if (temp >= pos)
		{
			return i;	
		}
		temp += m_chromosomes.at(i).second;
	}
	return m_chromosomes.size() - 1;

}

void Utility::pick_elite()
{
	int elite_size = elite_ratio * static_cast<double>(m_population_size);
	//std::cout<< "elite size: " << elite_size << std::endl;
	for (int i=0;i<elite_size;i++)
	{			
		m_chromosomes_copy.push_back(m_chromosomes.at(i));
	}
}

void Utility::mutate()
{
	RandomGenerators * rg = RandomGenerators::get_instance();
	int mutation_start = m_population_size * elite_ratio;
	for (int i=mutation_start;i<m_chromosomes_copy.size();i++)
	{			
		if (rg->get_random_double(0, 1) < mutation_rate)
		{
			m_chromosomes_copy.at(i).first.replace_gene(rg->get_random_int(0, globals::Upgradables::SIZE - 1), rg->get_random_int(0, m_chromosomes_copy.at(i).first.size()-1));
			m_chromosomes_copy.at(i).second = m_fitness_function(m_chromosomes_copy.at(i).first);
		}
	}
}


void Utility::crossover_chromosomes()
{
	const int number_of_crossovers = (1 - drop_rate) * (m_population_size - m_chromosomes_copy.size());
	//std::cout<<"number of crossovers: " << number_of_crossovers << "\n";

	for (int i=0; i< number_of_crossovers; ++i)
	{
		int index1 = select();
		int index2 = select();
		if (m_crossover_strategy == nullptr)
		{
			std::runtime_error("Utility::crossover_chromosomes: m_crossover_strategy not set");
		}
		Chromosome child = m_crossover_strategy->cross(m_chromosomes.at(index1).first, m_chromosomes.at(index2).first);
		m_chromosomes_copy.push_back(std::make_pair(child, m_fitness_function(child)));
	}
}

void Utility::fill_with_new()
{
	const int number_to_fill = m_population_size - m_chromosomes_copy.size();
	for (int i=0; i<number_to_fill; ++i)
	{
		Chromosome rnd = generate_random_chromosome(m_default_chromosome_size);
		m_chromosomes_copy.push_back(std::make_pair(rnd, m_fitness_function(rnd)));
	}
}

void Utility::fill_with_selection()
{
	const int number_to_fill = m_population_size - m_chromosomes_copy.size();
	for (int i=0; i< number_to_fill; ++i)
	{
		int pos = select();
		//std::cout << pos << std::endl;
		auto picked = m_chromosomes.at(pos).first;
		auto fitness = m_chromosomes.at(pos).second;
		if ((1.0/fitness)/3600 < 100)
		{
			std::cout << "fitness to low" << std::endl;
		}
		// std::cout << picked << ", fitness: " << 1.0 / m_chromosomes.at(pos).second << std::endl;
		m_chromosomes_copy.push_back(m_chromosomes.at(pos));
		//std::cout << 1.0 / m_chromosomes.at(pos).second / 3600 << std::endl;
	}
}

void Utility::resize()
{
	RandomGenerators *rnd = RandomGenerators::get_instance();
	for (int c=0;c<m_chromosomes_copy.size();c++)
	{
		Chromosome *ch = &m_chromosomes_copy.at(c).first;
		bool found = false;
		int i=0;
		for (;i<ch->size();i++)
		{
			if (ch->get(i) == globals::COLONIZATION_SHIP)
			{
				ch->remove_from(i+1);
				found = true;
				break;
			}
		}
		if (!found)
		{
			for(;i<m_default_chromosome_size;i++)
			{
				ch->append_gene(rnd->get_random_int(0, globals::Upgradables::SIZE-1));
			}
		}
		
		// m_chromosomes_copy.at(c).first = ch.at(c).begin(), ch.begin() + i);
	}
}

void Utility::run()
{
	m_chromosomes_copy.reserve(m_population_size);
	prepare_initial_population();
	print();

	for (int epoch=0; epoch<5000;++epoch)
	{
		std::cout<< "Epoch: " << epoch << ", ";
		m_chromosomes_copy.erase(m_chromosomes_copy.begin(), m_chromosomes_copy.end());
		pick_elite();
		crossover_chromosomes();
		resize();
		//std::cout << "before" << std::endl;
		//print_copy();
		//fill_with_new();
		fill_with_selection();
		//std::cout << "after!\n=================================================" << std::endl;
		//print_copy();
		mutate();
		m_chromosomes = m_chromosomes_copy;
		sort_chromosomes();
		std::cout << "best one: " << m_chromosomes.at(0).first << ", time: " << (1 / m_chromosomes.at(0).second)/3600 << "\n";
		assert (m_population_size == m_chromosomes.size());
	}
	print();
}
