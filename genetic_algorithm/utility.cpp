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
        ret.append_gene(rnd->get_random_int(0, 7));
    }

    for (int i=size/1;i<size;i++)
    {
        ret.append_gene(rnd->get_random_int(0, globals::Upgradables::SIZE-1));
    }
    
    return ret;
}

Chromosome Utility::generate_random_possible_chromosome(int size)
{
    Chromosome ret = Chromosome();
    ret.reserve(size);
    RandomGenerators *rnd = RandomGenerators::get_instance();
    for (int i=0;i<size;i++) {
        ret.append_gene(rnd->get_random_int(0, globals::Upgradables::SIZE-1));
        int counter = 0;
//		std::cout << ret << std::endl;
        while(m_fitness_function(ret) == 1e-100){
            ret.replace_gene(rnd->get_random_int(0, globals::Upgradables::SIZE-1), i);
            if(counter++ > 100) {
                return ret;
            }
        }
        // std::cout<<"i: " << i << std::endl;
    }
    return ret;
}

void Utility::prepare_initial_population()
{
    for (int i=0;i<m_population_size; ++i)
    {
        Chromosome chromosome = generate_random_possible_chromosome(m_default_chromosome_size);
        std::cout << i << std::endl;
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

void Utility::mutate_flip()
{
    RandomGenerators * rg = RandomGenerators::get_instance();
    int mutation_start = m_population_size * elite_ratio;
    for (int i=mutation_start;i<m_chromosomes_copy.size();i++)
    {			
		if (m_chromosomes_copy.at(i).first.size() > 2) 
		{
        	while (rg->get_random_double(0, 1) < mutation_rate)
        	{
        	    m_chromosomes_copy.at(i).first.replace_gene(rg->get_random_int(0, globals::Upgradables::SIZE - 1), rg->get_random_int(0, m_chromosomes_copy.at(i).first.size()-1));
        	    m_chromosomes_copy.at(i).second = m_fitness_function(m_chromosomes_copy.at(i).first);
        	}
		}
    }
}

void Utility::mutate_swap()
{
    RandomGenerators * rg = RandomGenerators::get_instance();
    int mutation_start = m_population_size * elite_ratio;
    for (int i=mutation_start;i<m_chromosomes_copy.size();i++)
    {		
        auto ch	= &m_chromosomes_copy.at(i).first;
        while (rg->get_random_double(0, 1) < swap_rate)
        {
            if (ch->size() <= 2) {
                break;
            }
            int pos = rg->get_random_int(0, ch->size() - 2);
            ch->swap(pos, pos+1);
            m_chromosomes_copy.at(i).second = m_fitness_function(m_chromosomes_copy.at(i).first);
        }
    }
}

void Utility::mutate_prune()
{
    RandomGenerators * rg = RandomGenerators::get_instance();
    int mutation_start = m_population_size * elite_ratio;
    for (int i=mutation_start;i<m_chromosomes_copy.size();i++)
    {		
        auto ch	= &m_chromosomes_copy.at(i).first;
        while (rg->get_random_double(0, 1) < prune_rate)
        {
            if (ch->size() <= 2) {
                break;
            }
            int pos = rg->get_random_int(0, ch->size() - 1);
            ch->remove(pos);
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
        m_chromosomes_copy.push_back(m_chromosomes.at(pos));
    }
}

void Utility::resize()
{
    RandomGenerators *rnd = RandomGenerators::get_instance();
    for (int c=0;c<m_chromosomes_copy.size();c++)
    {
        Chromosome *ch = &m_chromosomes_copy.at(c).first;
        bool found = false;
        int pos1 = ch->has(globals::ASTROPHYSICS);
        int pos2 = ch->has(globals::COLONIZATION_SHIP);
        int pos = std::max(pos1, pos2);
        // std::cout << pos << std::endl;
        if (pos1 != -1 && pos2 != -1)
        {
            ch->remove_from(pos+1);
            found = true;
        }

        if (!found)
        {
            for(int i=ch->size();i<m_default_chromosome_size;i++)
            {
                ch->append_gene(rnd->get_random_int(0, globals::Upgradables::SIZE-1));
            }
        }
        
        m_chromosomes_copy.at(c).second = m_fitness_function(*ch);
    }
}

void Utility::run()
{
    m_chromosomes_copy.reserve(m_population_size);
    prepare_initial_population();
    print();

    for (int epoch=0; epoch<500000;++epoch)
    {
        std::cout<< "Epoch: " << epoch << ", ";
        m_chromosomes_copy.erase(m_chromosomes_copy.begin(), m_chromosomes_copy.end());
        pick_elite();
        crossover_chromosomes(); 
        fill_with_selection();
        mutate_flip();
        mutate_swap();
        mutate_prune();
        resize();
        m_chromosomes = std::vector<std::pair<Chromosome, double> > (m_chromosomes_copy.begin(), m_chromosomes_copy.end());
        sort_chromosomes();
        std::cout << "best one: " << m_chromosomes.at(0).first << ", time: " << (1 / m_chromosomes.at(0).second)/3600 << " " << (1.0 / m_fitness_function(m_chromosomes.at(0).first))/3600 <<" "<< m_fitness_function(m_chromosomes.at(0).first) << "\n";
        assert (m_population_size == m_chromosomes.size());
    }
    print();
}
