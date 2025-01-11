#pragma once
#include<iostream>

#include "point.h"
#include "types.h"


class Environment;

class Actuator
{
    protected:
        Environment * env;
        std::string agent_name;

    public:
        void virtual act(instruction * ins) = 0;
        Actuator(Environment * env, std::string agent_name) 
        {
            this->env = env; 
            this->agent_name = agent_name; 
        }
        
        // ~Actuator(){}
        virtual ~Actuator(){}
};
