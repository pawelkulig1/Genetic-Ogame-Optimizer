#pragma once
#include "common_includes.h"

class GameObject;
class BuildQueue {
	static constexpr int queues = 3;
	bool m_empty[queues];
	double time_left[queues];
	int finished_index;
	GameObject* queue[queues];
	bool verify_index(int index) const;

public:
	BuildQueue();
	bool isEmpty() const;
	double getShortestTime() const;
	double getTime(int index);
	double passShortestTime();
	void passTime(double time);
	GameObject* getFinishedBuilding();
	int getFinishedIndex() const;
	bool addToQueue(int index, GameObject *obj, double construction_time);
	void clearQueue(int index);
	GameObject* at(int index);
};
