#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>
#include "agent.h"
#include "floor.h"
#include "point.h"
#include "types.h"

#include <unistd.h>


struct agent_info
{
    Agent* ptr;
    point position; 
    Floor floor_underneath;
};

class Environment
{
    public:
        // Environment(std::string path, bool is_multiagent = false);
        virtual ~Environment() {};

        virtual void move_agent(std::string agent_name, point movement_vector)=0;

        virtual bool add_agent(Agent* agent, point position) = 0;
        
        virtual bool clean(std::string agent_name, point relative_position) = 0;        

};
