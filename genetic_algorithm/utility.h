#pragma once

// #include "chromosome.h"
#include "crossover.h"
#include <functional>
#include <list>
#include <thread>
#include <future>

class Utility
{
	using chromosome = std::vector<int>;
	int m_population_size = 50;
	unsigned int  m_default_chromosome_size = 200;
	Crossover<int> *m_crossover_strategy;
	std::function<double (std::vector<int>)> m_fitness_function;
	std::vector<std::pair<chromosome, double> > m_chromosomes;
	std::vector<std::pair<chromosome, double> > m_chromosomes_copy;
	double drop_rate = 0.2;
	double mutation_rate = 0.1;
	double swap_rate = 0.1;
	double prune_rate = 0.1;
	double add_rate = 0.1;
	double elite_ratio = 0.1;
	double m_tournament_size = 30;

	double dynamic_mutation_rate = mutation_rate;
	double dynamic_swap_rate = swap_rate;
	double dynamic_prune_rate = prune_rate;
	double dynamic_add_rate = add_rate;

	void sort_chromosomes();
	void drop_weak();
	void crossover_chromosomes();
	void pick_elite();
	void mutate_flip();
	void mutate_swap();
	void mutate_prune();
	void mutate_add();
	void fill_with_new();
	void fill_with_selection();
	int select();
	int tournament_selection(int k);
	void print_copy();
	void resize();

public:
	chromosome generate_random_chromosome(int size);
	chromosome generate_random_possible_chromosome(size_t size);
	void prepare_initial_population();
	void set_crossover_strategy(Crossover<int> &crossover_strategy) {m_crossover_strategy = &crossover_strategy;}
	void set_population_size(int size) {m_population_size = size;}
	void set_fitness_function(std::function<double (chromosome)> fitness_function) {m_fitness_function = fitness_function;}
	void print();
	void run();
};
