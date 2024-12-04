#pragma once

#include "floor.h"
#include <string>
#include "point.h"
#include "types.h"
#include <iostream>

class Sensor
{
    protected:
        std::string name;
        Sensor(std::string name){this->name = name;}
    public:

        std::string get_name(){return name;}

        percept virtual sense(sensor_input * i) = 0;
        ~Sensor() {}
};
