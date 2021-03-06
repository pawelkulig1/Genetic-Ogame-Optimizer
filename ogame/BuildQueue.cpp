#include "BuildQueue.h"
#include "GameObject.h"
#include <limits>
#include <cassert>

BuildQueue::BuildQueue()
{
    for (int i=0;i<queues;i++)
    {
        m_empty[i] = true;
        time_left[i] = 0;
        queue[i] = nullptr;
    }
    finished_index = -1;
}

bool BuildQueue::isEmpty(int index) const
{
    if(index == -1)
    {
        for (int i=0;i<queues;i++)
        {
            if (!m_empty[i]) return false;
        }
        return true;
    }
    else
    {
        verify_index(index);
        return m_empty[index];
    }
    
}

double BuildQueue::getShortestTime() const
{
    bool all = true;
    for(int i=0;i<queues;i++)
    {
        if (!m_empty[i]) {
            all = false;
        }
    }
    if (all) return 0;

    double min_time = std::numeric_limits<double>::max();
    for (int i=0;i<queues;i++)
    {
        if (!m_empty[i])
        {
            min_time = std::min(min_time, time_left[i]);
        }
    }
    return min_time;
}

double BuildQueue::passShortestTime()
{
    double shortestTime = getShortestTime();
    passTime(shortestTime);
    return shortestTime;
}

void BuildQueue::passTime(double time)
{
    for (int i=0;i<queues;i++)
    {
        if (!m_empty[i])
        {
            time_left[i] -= time;
            if (time_left[i] <= 0 && queue[i] != nullptr) 
            {
                finished_index = i;
            }
        }
    }
}

GameObject* BuildQueue::getFinishedBuilding()
{
    verify_index(finished_index);
    if (finished_index != -1)
    {
        return queue[finished_index];
    }
}	

int BuildQueue::getFinishedIndex() const
{
    if (finished_index != -1)
    {
        return finished_index;
    }
    return static_cast<int>(globals::QueueIndex::NONE);
}

bool BuildQueue::addToQueue(int index, GameObject *obj, double construction_time)
{
    verify_index(index);
    if (!m_empty[index]) {return false;}
    m_empty[index] = false;
    time_left[index] = construction_time;
    queue[index] = obj;
    return true;
}

void BuildQueue::clearQueue(int index)
{
    verify_index(index);
    assert (time_left[index] <= 0);

    m_empty[index] = true;
    time_left[index] = 0.0;
    queue[index] = nullptr;

    for(int i=0;i<queues;i++) 
    {
        if (time_left[i] <= 0 && queue[i] == nullptr)
        {
            m_empty[i] = true;
            time_left[i] = 0.0;
        }
    }
}

void BuildQueue::lockQueue(int index, double time)
{
    verify_index(index);
    if (m_empty[index])
    {
        time_left[index] = time;
        m_empty[index] = false;
        queue[index] = nullptr;
    }
}

double BuildQueue::getTime(int index)
{
    verify_index(index);
    return time_left[index];
}

bool BuildQueue::verify_index(int index) const
{
    assert (index >= 0);
    assert (index < static_cast<int>(globals::QueueIndex::END));
    return true;
}

GameObject* BuildQueue::at(int index) {
    assert (index >= 0);
    assert (index < queues);
    return queue[index];
}