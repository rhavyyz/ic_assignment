#pragma once
#include "sensor.h"

class DirtSensor : public Sensor
{

    public:
        DirtSensor(std::string name) : Sensor(name)  {}

        percept sense(sensor_input * i)
        {

            if (i->floor != Floor::dirty and i->floor != Floor::clean)
                throw "not suitable";

            return {get_name(), (i->floor == Floor::dirty ? 1 : 0)};
        }

};