#pragma once
#include "actuator.h"
#include "environment.h"

class CleanerActuator : public Actuator
{

    public:
        CleanerActuator(Environment * env, std::string agent_name) 
        : Actuator(env, agent_name){}


        void act(instruction * ins)
        {
            env->clean(agent_name, {0,0});
        }
};
