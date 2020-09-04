#include "utility.h"
#include "common_includes.h"
#include "random_generators.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <fstream>


Utility::chromosome Utility::generate_random_chromosome(int size)
{
    chromosome ret;
    ret.reserve(size);
    RandomGenerators *rnd = RandomGenerators::get_instance();
    for (int i=0;i<size/1;i++)
    {
        ret.push_back(rnd->get_random_int(0, 7));
    }

    for (int i=size/1;i<size;i++)
    {
        ret.push_back(rnd->get_random_int(0, static_cast<int>(globals::Upgradables::SIZE)-1));
    }

    return ret;
}

Utility::chromosome Utility::generate_random_possible_chromosome(size_t size)
{
    chromosome ret;
    ret.reserve(size);
    std::vector<int> structures(static_cast<int>(globals::Upgradables::SIZE)-1);
    int i = 0;
    std::iota(structures.begin(), structures.end(), 0);
    std::random_device rd;
    std::mt19937 g(rd());
    for (size_t i=0;i<size;)
    {
        bool impossible = true;

        std::shuffle(structures.begin(), structures.end(), g);
        ret.push_back(static_cast<int>(globals::Upgradables::SIZE));
        for (auto &e: structures)
        {
            ret.at(i) = e;
            if (m_fitness_function(ret) != 1e-100)
            {
                impossible = false;
                break;
            }
        }
        if (impossible)
        {
            break;
        }
        i++;
    }
    return ret;
}

void Utility::generate_random_possible_chromosome(std::promise<chromosome> * promObj)
{
    chromosome ret;
    const auto size = m_default_chromosome_size;
    ret.reserve(size);
    std::vector<int> structures(static_cast<int>(globals::Upgradables::SIZE)-1);
    int i = 0;
    std::iota(structures.begin(), structures.end(), 0);
    std::random_device rd;
    std::mt19937 g(rd());
    for (size_t i=0;i<size;)
    {
        bool impossible = true;

        std::shuffle(structures.begin(), structures.end(), g);
        ret.push_back(static_cast<int>(globals::Upgradables::SIZE));
        for (auto &e: structures)
        {
            ret.at(i) = e;
            if (m_fitness_function(ret) != 1e-100)
            {
                impossible = false;
                break;
            }
        }
        if (impossible)
        {
            break;
        }
        i++;
    }
    return promObj->set_value(ret);
}

void Utility::prepare_initial_population()
{
    // std::vector<std::thread> threads;
    // std::vector<std::promise<chromosome> > promises;
    std::vector<std::future<chromosome> > futures;

    for (int i=0;i<m_population_size; ++i)
    {
        futures.push_back(std::async([this](){return generate_random_possible_chromosome(m_default_chromosome_size);}));
    }
    for(int i=0;i<m_population_size;i++)
    {
        auto ch = futures[i].get();
        std::cout << "ch" << i << '\n';
        m_chromosomes.push_back(std::make_pair(ch, m_fitness_function(ch)));
    }

    sort_chromosomes();

}

void Utility::sort_chromosomes()
{
    std::vector<std::future<double> > futures;
    for (auto &el: m_chromosomes)
    {
        futures.push_back(std::async([el, this](){return m_fitness_function(el.first);}));
    }

    for (size_t i{0}; i < m_chromosomes.size(); i++)
    {
        m_chromosomes[i].second = futures[i].get();
    }

    std::sort(m_chromosomes.begin(), m_chromosomes.end(), [](const std::pair<std::vector<int>, double> &p1, const std::pair<std::vector<int>, double> &p2)
            { return p1.second > p2.second;});
}

void Utility::print()
{
    for (int i=0;i<m_population_size;++i)
    {
        for (const auto el: m_chromosomes.at(i).first)
        {
            std::cout<< el << ",";
        }
        std::cout << " " << m_chromosomes[i].second << " " << (1 / m_chromosomes[i].second) / 3600 << " hours\n";
    }
}

void Utility::print_copy()
{
    std::cout << "m_chromosomes_copy.size(): " << m_chromosomes_copy.size() << std::endl;
    for (size_t i=0;i<m_chromosomes_copy.size();++i)
    {
        for (const auto el: m_chromosomes_copy.at(i).first)
        {
            std::cout<< el << ",";
        }
        std::cout << " " << m_chromosomes_copy[i].second << " " << (1 / m_chromosomes_copy[i].second) / 3600 << " hours\n";
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
    for (const std::pair<chromosome, double> pair: m_chromosomes)
    {
        sum_of_fitness += pair.second;
    }
    double temp = 0;

    double pos = RandomGenerators::get_instance()->get_random_double(0, sum_of_fitness);
    for(size_t i=0; i< m_chromosomes.size();i++)
    {
        if (temp >= pos)
        {
            return i;
        }
        temp += m_chromosomes.at(i).second;
    }
    return m_chromosomes.size() - 1;
}

int Utility::tournament_selection(int k)
{
    //based on fact that population is sorted
    std::vector<int> rands;
    rands.reserve(k);

    RandomGenerators *rnd = RandomGenerators::get_instance();

    std::generate_n(std::back_inserter(rands), k, [&](){return rnd->get_random_int(0, m_population_size-1);});
    auto out = std::distance(rands.begin(), std::min_element(rands.begin(), rands.end()));

    assert(out >= 0 && out < m_population_size);
    return out;
}

void Utility::pick_elite()
{
    int elite_size = elite_ratio * static_cast<double>(m_population_size);
    for (int i=0;i<elite_size;i++)
    {
        m_chromosomes_copy.push_back(m_chromosomes.at(i));
    }
}

void Utility::mutate_flip()
{
    RandomGenerators * rg = RandomGenerators::get_instance();
    for (auto &c: m_chromosomes_copy)
    {
		if (c.first.size() > 2)
		{
        	while (rg->get_random_double(0, 1) < dynamic_mutation_rate)
        	{
                const int pos = rg->get_random_int(0, c.first.size()-1);
                const int new_val = rg->get_random_int(0, static_cast<int>(globals::Upgradables::SIZE) - 1);
        	    c.first.at(pos) = new_val;
        	}
		}
    }
}

void Utility::mutate_swap()
{
    RandomGenerators * rg = RandomGenerators::get_instance();
    // int mutation_start = 1;// m_population_size * elite_ratio;
    for (auto &c: m_chromosomes_copy)
    {
        // auto ch	= &m_chromosomes_copy.at(i).first;
        while (rg->get_random_double(0, 1) < dynamic_swap_rate)
        {
            if (c.first.size() <= 2) {
                break;
            }
            int pos = rg->get_random_int(0, c.first.size() - 2);
            std::swap(c.first.at(pos), c.first.at(pos+1));
        }
    }
}

void Utility::mutate_prune()
{
    RandomGenerators * rg = RandomGenerators::get_instance();
    //int mutation_start = 1; //m_population_size * elite_ratio;
    for (auto &c: m_chromosomes_copy)
    {
        while (rg->get_random_double(0, 1) < dynamic_prune_rate)
        {
            if (c.first.size() <= 2) {
                break;
            }
            int pos = rg->get_random_int(0, c.first.size() - 1);
            c.first.erase(c.first.begin() + pos);
        }
    }
}

void Utility::mutate_add()
{
	RandomGenerators *rg = RandomGenerators::get_instance();
	// int mutation_start = 1;
    for (auto &c: m_chromosomes_copy)
    {
        while (rg->get_random_double(0, 1) < dynamic_add_rate)
        {
            if (c.first.size() <= 2) {
                break;
            }
            int pos = rg->get_random_int(0, c.first.size() - 1);
			int new_gene = rg->get_random_int(0, static_cast<int>(globals::Upgradables::SIZE) - 1);
			c.first.insert(c.first.begin() + pos, new_gene);
        }
    }
}

void Utility::crossover_chromosomes()
{
    const int number_of_crossovers = (1 - drop_rate) * (m_population_size - m_chromosomes_copy.size());
    for (int i=0; i< number_of_crossovers / 2; ++i)
    {
        int index1 = tournament_selection(m_tournament_size);
        int index2 = tournament_selection(m_tournament_size);
        if (m_crossover_strategy == nullptr)
        {
            std::runtime_error("Utility::crossover_chromosomes: m_crossover_strategy not set");
        }
        auto children = m_crossover_strategy->cross(m_chromosomes.at(index1).first, m_chromosomes.at(index2).first);

        m_chromosomes_copy.push_back(std::make_pair(children.first, 0));
        m_chromosomes_copy.push_back(std::make_pair(children.second, 0));
    }
}

void Utility::fill_with_new()
{
    const int number_to_fill = m_population_size - m_chromosomes_copy.size();
    for (int i=0; i<number_to_fill; ++i)
    {
        chromosome rnd = generate_random_chromosome(m_default_chromosome_size);
        m_chromosomes_copy.push_back(std::make_pair(rnd, 0));
    }
}

void Utility::fill_with_selection()
{
    const int number_to_fill = m_population_size - m_chromosomes_copy.size();
    for (int i=0; i< number_to_fill; ++i)
    {
        int pos = tournament_selection(m_tournament_size);
        m_chromosomes_copy.push_back(m_chromosomes.at(pos));
    }
}

void Utility::resize()
{

    // for (auto &c: m_chromosomes_copy)
    // {
    //     if (c.first.size() > m_default_chromosome_size)
    //     {
    //         c.first.erase(c.first.begin() + m_default_chromosome_size - 1, c.first.end());
    //     }
    // }
    RandomGenerators *rnd = RandomGenerators::get_instance();
    for (int c=0;c<m_chromosomes_copy.size();c++)
    {
        auto ch = &m_chromosomes_copy.at(c).first;
        bool found = false;
        auto pos1 = std::find(ch->begin(), ch->end(), static_cast<int>(globals::Upgradables::ASTROPHYSICS));
        auto pos2 = std::find(ch->begin(), ch->end(), static_cast<int>(globals::Upgradables::COLONIZATION_SHIP));
        auto pos = std::max(pos1, pos2);
        if (pos1 != ch->end() && pos2 != ch->end())
        {
            ch->erase(pos + 1, ch->end());
            found = true;
        }

        if (!found)
        {
            ch->erase(ch->begin(), ch->end());
            auto temp = tournament_selection(m_tournament_size);//generate_random_possible_chromosome(m_default_chromosome_size);
            if (m_chromosomes_copy.at(temp).first.size() > 0)
            {
                ch->insert(ch->begin(), m_chromosomes_copy.at(temp).first.begin(), m_chromosomes_copy.at(temp).first.end());
            }
            else
            {
                auto random_chromosome = generate_random_possible_chromosome(m_default_chromosome_size);
                ch->insert(ch->begin(), random_chromosome.begin(), random_chromosome.end());
            }
        }
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
		mutate_add();
        //resize();
        m_chromosomes.erase(m_chromosomes.begin(), m_chromosomes.end());
        m_chromosomes.insert(m_chromosomes.begin(), m_chromosomes_copy.begin(), m_chromosomes_copy.end());
        sort_chromosomes();

        std::cout << "best one: ";
        for (const auto el: m_chromosomes.at(0).first)
        {
            std::cout << el << ",";
        }
        std::cout << " fitness: " << m_chromosomes.at(0).second << '\n';
        assert (m_population_size == m_chromosomes.size());
    }
    print();
}
