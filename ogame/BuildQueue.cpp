#include "BuildQueue.h"
#include "GameObject.h"
#include <limits>
#include <cassert>
#include <algorithm>
#include <functional>
// #include <cstring>

BuildQueue::BuildQueue()
{
    queues.fill(Queue());
}

BuildQueue::BuildQueue(const BuildQueue& bq)
{
    queues = bq.queues;
}

BuildQueue::BuildQueue(BuildQueue&& bq) noexcept
{
    queues = std::move(bq.queues);
}

BuildQueue& BuildQueue::operator=(BuildQueue&& bq) noexcept
{
    if (&bq == this) return *this;
    queues = std::move(bq.queues);
    return *this;
}

BuildQueue& BuildQueue::operator=(const BuildQueue& bq)
{
    if (&bq == this) return *this;
    queues = bq.queues;
    return *this;
}

bool BuildQueue::isEmpty(int index) const
{
    if (index == -1) {return std::all_of(queues.begin(), queues.end(), [](const Queue& q){return q.m_empty;});}
    else
    {
        verify_index(index);
        return queues[index].m_empty;
    }
}

double BuildQueue::getShortestTime() const
{
    if (std::all_of(queues.begin(), queues.end(), [](const Queue& q){return q.m_empty;})) {return 0;}

    double min_time = std::numeric_limits<double>::max();

    for (int i=0;i<m_number_of_queues;i++)
    {
        if (!queues[i].m_empty)
        {
            min_time = std::min(min_time, queues[i].m_time_left);
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
    std::for_each(queues.begin(), queues.end(), [time](Queue& q) {
        if (!q.m_empty) q.m_time_left -= time;
    });
}

int BuildQueue::getFinishedBuildingId()
{
    auto it = std::find_if(queues.begin(), queues.end(), [](const Queue& q) {
        return (!q.m_empty && q.m_time_left <= 0 && q.id != -1);
    });
    assert (it != queues.end());
    return it->id;
}

int BuildQueue::getFinishedIndex() const
{
    auto it = std::find_if(queues.begin(), queues.end(), [](const Queue& q) {
        return (!q.m_empty && q.m_time_left <= 0 && q.id != -1);
    });
    // assert (it != queues.end());
    //legacy
    if (it == queues.end())
    {
        return 0;
    }
    return std::distance(queues.begin(), it);
}

bool BuildQueue::addToQueue(int index, int id, double construction_time)
{
    verify_index(index);
    if (!queues[index].m_empty) {return false;}
    queues[index].m_empty = false;
    queues[index].m_time_left = construction_time;
    queues[index].id = id;
    return true;
}

void BuildQueue::clearQueue(int index)
{
    verify_index(index);
    assert (queues[index].m_time_left <= 0);

    queues[index].m_empty = true;
    queues[index].m_time_left = 0.0;
    queues[index].id = -1;

    std::for_each(queues.begin(), queues.end(), [](Queue& q){
        if (q.m_time_left <= 0 && q.id == -1) {q.m_empty = true; q.m_time_left = 0.0;}
    });
}

void BuildQueue::lockQueue(int index, double time)
{
    verify_index(index);
    if (queues[index].m_empty)
    {
        queues[index].m_time_left = time;
        queues[index].m_empty = false;
        queues[index].id = -1;
    }
}

double BuildQueue::getTime(int index)
{
    verify_index(index);
    return queues[index].m_time_left;
}

bool BuildQueue::verify_index(int index) const
{
    assert (index >= -1);
    assert (index < static_cast<int>(globals::QueueIndex::END));
    return true;
}

int BuildQueue::at(int index) {
    assert (index >= 0);
    assert (index < m_number_of_queues);
    return queues[index].id;
}
