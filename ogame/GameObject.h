#pragma once
#include "Resources.h"
#include "common_includes.h"
#include <list>
#include <array>
#include <math.h>

static consteval std::array<double, 10> generate_nanite_cache()
{
    std::array<double, 10> temp;
    for(int i = 0; i < 10; i++)
    {
        temp[i] = pow(0.5, i);
    }
    return temp;
}


class GameObject
{
public:
	using Requirements = std::pair<int, int>;
protected:
	Resources defaultCost;
	std::string name;
	std::list<Requirements> m_requirements;
	globals::QueueIndex queue_index;
    
    static constexpr std::array<double, 10> nanite_cache = generate_nanite_cache();

public:
	GameObject(Resources default_cost);
	GameObject(const GameObject& go);
	GameObject(GameObject&& go) noexcept;
	virtual ~GameObject() {}
    virtual const Resources &getDefaultCost() const;
    virtual void operator++() = 0;
    virtual double getConstructionTime(int robot_factory_shipyard_level, int nanite_factory_level) const = 0;
    virtual Resources getUpgradeCost() const = 0;
	std::list<Requirements> get_requirements();
	void setName(std::string name);
	std::string getName() const;
	globals::QueueIndex getQueueIndex() const;
    friend std::ostream &operator<<(std::ostream &out, const GameObject &b);
};
