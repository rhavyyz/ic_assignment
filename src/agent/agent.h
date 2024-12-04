#pragma once
#include <map>
#include <vector>
#include <thread>
#include "actuator.h"
#include "sensor_manager.h"
#include <semaphore>

// #include "environment.h"


class Environment;

class Agent
{
    private:
        std::thread * t;
        
    protected:
        std::map<std::string, Actuator*> actuaors;
        SensorManager * sensors;
        std::string name;

    public:
        void virtual reason(std::map<std::string, percept> perceptions) = 0;
        void run();
        void wait();
        void join();

        ~Agent();
        Agent(Environment * env, std::string name);
        std::string get_name() { return this->name; }
        SensorManager * get_sensor_manager() { return sensors; }
};

// #include "environment.h"
