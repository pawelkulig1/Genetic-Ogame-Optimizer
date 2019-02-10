//
// Created by Paweł Kulig on 2019-01-12.
//

#ifndef OGAME_BUILDING_H
#define OGAME_BUILDING_H


#include "Resources.h"

#define planetTemperature 25
#define PoziomFabrRobot 0
#define PoziomFabNanit 0

class Building {
protected:
    int lvl;
    const Resources defaultCost;
    const double costRatio;
    double constructionTimeSec;
    std::string name;
public:
    const std::string &getName() const;

    void setName(const std::string &name);

public:

    Building(const Resources &defaultCost, const double costRatio = 2);

    virtual Resources getNextLevelCost() const;

    virtual int getLvl() const;

    virtual const Resources &getDefaultCost() const;

    virtual const double getCostRatio() const;

    virtual void setLvl(int lvl);

    virtual void operator++();

    double getConstructionTime();

    friend std::ostream &operator<<(std::ostream &out, const Building &b);
};


#endif //OGAME_BUILDING_H
