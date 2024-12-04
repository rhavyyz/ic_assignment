#pragma once
#include "sensor.h"
#include "floor.h"


class CollisionSensor : public Sensor
{
    std::set<Floor> prohibited_floors = {Floor::wall, Floor::agent, Floor::empty};

    public:
        CollisionSensor(std::string name) : Sensor(name)  {}

        percept sense(sensor_input * i)
        {
            return {get_name(), prohibited_floors.count(i->floor)};
        }

};