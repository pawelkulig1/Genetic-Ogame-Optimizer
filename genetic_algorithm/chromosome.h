#pragma once
#include <vector>

class Chromosome
{
public:
	using chromosome_type = int;
	using data_store = std::vector<chromosome_type>;

	Chromosome() = default;
	void append_gene(chromosome_type gene);
	void insert_gene(chromosome_type gene, int index);
	void replace_gene(chromosome_type gene, int index);
	chromosome_type get(int index) const;
	const std::vector<chromosome_type> &get_vector() const;
	int size() const {return m_chromosome.size();};
	void set_chromosome(data_store &chromosome);
	void reserve(size_t size);
	void set_chromosome(int pos, data_store::const_iterator beg, const data_store::const_iterator end);
	data_store::const_iterator begin() const;
	data_store::const_iterator end() const;	

	friend std::ostream &operator<<(std::ostream &out, const Chromosome &chromosome);

private:
	std::vector<chromosome_type> m_chromosome;

};
