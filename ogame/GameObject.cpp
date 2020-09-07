#include "GameObject.h"
#include <cassert>

GameObject::GameObject(Resources default_cost): defaultCost(default_cost)
{
	m_requirements = {};
	queue_index = globals::QueueIndex::NONE;
}

GameObject::GameObject(const GameObject& go)
{
	defaultCost = go.defaultCost;
	name = go.name;
	m_requirements = std::list<Requirements >(go.m_requirements);
	queue_index = go.queue_index;
}

GameObject::GameObject(GameObject&& go) noexcept
{
	defaultCost = go.defaultCost;
	name = go.name;
	m_requirements = std::move(go.m_requirements);
	queue_index = go.queue_index;
}

std::ostream &operator<<(std::ostream &out, const GameObject &b) {
    out << "Name: " << b.name << ", ";
	out << "Requirements: \n";
	for (GameObject::Requirements req: b.m_requirements)
	{
		out << "name: " << req.first << " " << "lvl: " << req.second << "\n";
	}
    return out;
}

const Resources &GameObject::getDefaultCost() const {
    return defaultCost;
}

std::string GameObject::getName() const {
    return name;
}

void GameObject::setName(std::string name) {
    GameObject::name = name;
}

globals::QueueIndex GameObject::getQueueIndex() const
{
	assert (static_cast<int>(queue_index) >= 0);
	return queue_index;
}

std::list<GameObject::Requirements> GameObject::get_requirements() {
	return m_requirements;
}
