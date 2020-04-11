#include "utility.h"
#include "common_includes.h"
#include "random_generators.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

Chromosome Utility::generate_random_chromosome(int size)
{
	Chromosome ret = Chromosome();
	ret.reserve(size);
	RandomGenerators *rnd = RandomGenerators::get_instance();
	for (int i=0;i<size;i++)
	{
		ret.append_gene(rnd->get_random_int(0, globals::Upgradables::SIZE - 1));
	}
	
	//std::vector<int> to_skip{0};
	//std::vector<int> to_pick;
	//const int pick_size = globals::Upgradables::SIZE - to_skip.size();
	//to_pick.reserve(pick_size);

	
	//for(int i=0;i<globals::Upgradables::SIZE;i++)
	//{
	//	if (std::any_of(to_skip.begin(), to_skip.end(), [i](int skip){return i != skip;}))
	//	{
	//		to_pick.push_back(i);
	//	}
	//}

	//for (int i=10;i<size;i++)
	//{
	//	int from = rand()%to_pick.size();
	//	int to = rand()%ret.size();
	//	ret.insert_gene(to_pick[from], to);
	//}
	return ret;
}

void Utility::prepare_initial_population()
{
	for (int i=0;i<m_population_size; ++i)
	{
		Chromosome chromosome = generate_random_chromosome(80);
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
		std::cout<<m_chromosomes[i].first << " " << m_chromosomes[i].second << " " << (1 / m_chromosomes[i].second) / 3600 << "\n";
	}
}

void Utility::print_copy()
{
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
	//std::uniform_real_distribution<double> dist(0, sum_of_fitness);
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
	std::cout<< "elite size: " << elite_size << std::endl; 

	for (int i=0;i<elite_size;i++)
	{			
		m_chromosomes_copy.push_back(m_chromosomes.at(i));
	}
}

void Utility::mutate()
{
	for (int i=0;i<m_chromosomes_copy.size();i++)
	{			
		if (RandomGenerators::get_instance()->get_random_double(0, 1) < mutation_rate)
		{
			m_chromosomes_copy.at(i).first.replace_gene(RandomGenerators::get_instance()->get_random_int(0, globals::Upgradables::SIZE - 1), RandomGenerators::get_instance()->get_random_int(0, m_chromosomes_copy.at(i).first.size()-1));
		}
	}
}


void Utility::crossover_chromosomes()
{
	const int number_of_crossovers = m_population_size - m_chromosomes_copy.size();
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

void Utility::run()
{
	m_chromosomes_copy.reserve(m_population_size);
	prepare_initial_population();
	print();

	for (int epoch=0; epoch<1500;++epoch)
	{
		std::cout<< "Epoch: " << epoch << "\n";
		m_chromosomes_copy.erase(m_chromosomes_copy.begin(), m_chromosomes_copy.end());
		pick_elite();
		print_copy();
		crossover_chromosomes();
		//print_copy();
		mutate();
		m_chromosomes = m_chromosomes_copy;
		sort_chromosomes();
		//print();
	}
	print();
}
