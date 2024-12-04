#include "agent.h"
#include <thread>
#include "types.h"

void monitor(Agent * agent)
{
    while (true)
    {
        std::cout << "Loop" << std::endl;
        agent->reason(agent->get_sensor_manager()->consume_event());
    }

    delete agent;
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


        std::cout << "ficou joining" << std::endl;
        t->join();
        std::cout << "joinou" << std::endl;

        return;
    }

    throw "It is not possible to join 2 times the same agent";
}

Agent::~Agent()
{
    delete sensors;

    for(auto [name, actuator] : actuaors)
        delete actuator;
}
