#pragma once

#include "chromosome.h"
#include "crossover.h"
#include <functional>
#include <list>

class Utility
{
	int m_population_size = 100;
	int m_default_chromosome_size = 200;
	Crossover *m_crossover_strategy;
	std::function<double (Chromosome)> m_fitness_function;
	std::vector<std::pair<Chromosome, double> > m_chromosomes;
	std::vector<std::pair<Chromosome, double> > m_chromosomes_copy;
	double drop_rate = 0.3;
	double mutation_rate = 0.1;
	double swap_rate = 0.3;
	double prune_rate = 0.3;
	double elite_ratio = 0.1;

	void sort_chromosomes();
	void drop_weak();
	void crossover_chromosomes();
	void pick_elite();
	void mutate_flip();
	void mutate_swap();
	void mutate_prune();
	void fill_with_new();
	void fill_with_selection();
	int select();
	void print_copy();
	void resize();

public:
	Chromosome generate_random_chromosome(int size);
	Chromosome generate_random_possible_chromosome(int size);
	void prepare_initial_population();
	void set_crossover_strategy(Crossover &crossover_strategy) {m_crossover_strategy = &crossover_strategy;}
	void set_population_size(int size) {m_population_size = size;}
	void set_fitness_function(std::function<double (Chromosome)> fitness_function) {m_fitness_function = fitness_function;}
	void print();
	void run();
};
