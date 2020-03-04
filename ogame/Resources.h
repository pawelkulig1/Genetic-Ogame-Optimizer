//
// Created by Paweł Kulig on 2019-01-12.
//

#ifndef OGAME_RESOURCES_H
#define OGAME_RESOURCES_H

#include <iostream>

#pragma once

class Resources {
public:
	using data_type = double;
private:
    data_type metal = 0;
    data_type crystal = 0;
    data_type deuterium = 0;
    data_type energy = 0;

public:
    Resources::data_type getEnergy() const;
	
    void setEnergy(data_type energy);

    Resources();

    Resources(data_type, data_type);

    Resources(data_type, data_type, data_type);

    Resources(data_type, data_type, data_type, data_type);

    data_type getMetal(void);

    data_type getCrystal(void);

    data_type getDeuterium();

    data_type at(int n);

    void setMetal(data_type);

    void setCrystal(data_type);

    void setDeuterium(data_type);

    Resources operator+(Resources);

    Resources operator-(Resources);

    Resources operator*(data_type);

    Resources operator^(data_type);

    Resources operator/(data_type);

    Resources operator*(data_type) const;

    bool operator>=(Resources);

	bool operator>(Resources);

	bool operator>(data_type required);

    friend std::ostream &operator<<(std::ostream &stream, const Resources &resources);
};


#endif //OGAME_RESOURCES_H
