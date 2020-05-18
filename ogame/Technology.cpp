#include "Technology.h"

Technology::Technology(Resources default_cost, double cost_ratio) : Structure(default_cost, cost_ratio)
{	
	queue_index = globals::QueueIndex::TECHNOLOGY;
}

double Technology::getConstructionTime(int labolatory_level, int not_important) const {
    Resources nlc = getUpgradeCost();
    return (3600 * (nlc.at(0) + nlc.at(1)) / (1000 * (labolatory_level+ 1)));
}
