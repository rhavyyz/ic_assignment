#include "agent.h"
#include <thread>
#include "types.h"
#include <iostream>

void monitor(Agent * agent)
{
    while (!agent->get_cleaned_all())
        agent->reason(agent->get_sensor_manager()->consume_event());
}

Agent::Agent(Environment * env, std::string name)
{
    this->name = name;
}

void Agent::run()
{
    this->t = new std::thread(monitor, this);        
}

void Agent::join()
{
    if(t->joinable())
    {
        t->join();
    }
    else
        throw "It is not possible to join 2 times the same agent";
}

Agent::~Agent()
{
    delete sensors;

    for(auto [name, actuator] : actuaors)
        delete actuator;
}
