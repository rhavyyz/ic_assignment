#pragma once
#include "sensor.h"

class DirtSensor : public Sensor
{

    public:
        DirtSensor(std::string name) : Sensor(name)  {}

        percept sense(sensor_input * i)
        {
            return {get_name(), (i->floor == Floor::dirty ? 1 : 0)};
        }

};