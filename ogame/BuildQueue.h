#pragma once
#include "common_includes.h"
#include <array>
#include <list>
#include <vector>

// class GameObject;
class BuildQueue {
	struct Queue {
		bool m_empty = true;
		double m_time_left = 0;
		int id = -1;
	};

	static constexpr int m_number_of_queues = 3;
	std::array<Queue, m_number_of_queues> queues;
	//int m_finished_index;

	bool verify_index(int index) const;

public:
	BuildQueue();
	BuildQueue(const BuildQueue& bq);
	BuildQueue(BuildQueue&& bq) noexcept;
	BuildQueue& operator=(BuildQueue&& bq) noexcept;
	BuildQueue& operator=(const BuildQueue& bq);
	bool isEmpty(int index=-1) const;
	double getShortestTime() const;
	double getTime(int index);
	double passShortestTime();
	void passTime(double time);
	int getFinishedBuildingId();
	int getFinishedIndex() const;
	bool addToQueue(int index, int id, double construction_time);
	void clearQueue(int index);
	void lockQueue(int index, double time);
	int at(int index);
};
