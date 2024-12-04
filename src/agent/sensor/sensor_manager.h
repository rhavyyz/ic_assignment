#pragma once

#include "sensor.h"
#include "queue"
#include <map>
#include <vector>
#include <semaphore>
#include "types.h"

class SensorManager
{
    private:
        std::queue<sensor_input> events;
        std::vector<Sensor*> sensors;
        std::counting_semaphore<(int)1e5> sem = std::counting_semaphore<(int)1e5>(0);

    public:
        void add_event(sensor_input s) 
        { 
            events.push(s); 
            sem.release();
        }
        
        SensorManager(
                        std::vector<Sensor *> sensors
                    )
        {
            this->sensors = sensors;
        }

        bool add_sensor(Sensor * s)
        {
            for(Sensor* sensor : sensors)
                if(sensor->get_name() == s->get_name())
                    return false;
            sensors.push_back(s);
            return true;
        }

        std::map<std::string, percept> consume_event()
        {
            sem.acquire();  
            std::map<std::string, percept> res;
            sensor_input event = events.front();
            events.pop();
            for(Sensor* sensor : sensors)
            {
                auto e = sensor->sense(&event);
            
                res.insert({e.label, e});
            }


            return res;
        }

        ~SensorManager()
        {
            for(Sensor* sensor : sensors)
                delete sensor;
        }
};