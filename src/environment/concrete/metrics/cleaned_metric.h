#pragma once
#include "environment.h"
#include "logger.h"


class CleanedMetric : public Environment
{
    private:
        Environment * child = nullptr;
        int code = 0;

    public:

        int get_metric(){ return code; }

        CleanedMetric(Environment * child) 
        { 
            this->child = child; 

            Logger::save({std::string("metrics"), "cleaned_metric"}, std::to_string(get_metric()));
        }

        // Environment(std::string path, bool is_multiagent = false);
        virtual ~CleanedMetric() { delete child; }

        virtual void move_agent(std::string agent_name, point movement_vector) 
        {
            return child->move_agent(agent_name, movement_vector);
        }

        virtual bool add_agent(Agent* agent, point position) 
        {
            return child->add_agent(agent, position);
        }
        
        virtual bool clean(std::string agent_name, point relative_position)
        {
            bool res = child->clean(agent_name, relative_position);

            if(res)
            {
                code++;

                Logger::save({std::string("metrics"), "cleaned_metric"}, std::to_string(get_metric()));
            }

            return res;
        }     

};
