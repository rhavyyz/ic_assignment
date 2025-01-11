#pragma once

#include "actuator.h"
#include "environment.h"

class MovementActuator : public Actuator
{

    public:
        MovementActuator(Environment * env, std::string agent_name) 
        : Actuator(env, agent_name){}


        void act(instruction * ins)
        {
            env->move_agent(agent_name, ins->movement_vector);
        }
};
