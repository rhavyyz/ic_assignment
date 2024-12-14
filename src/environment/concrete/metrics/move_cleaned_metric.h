#pragma once

#include "concrete/metrics/cleaned_metric.h"
#include "logger.h"

class MoveCleanedMetric : public Environment
{
    private:
        CleanedMetric * child = nullptr;

        int  code = 0;

    public:

        MoveCleanedMetric(Environment * env)
        {
            child = new CleanedMetric(env);

            Logger::save({std::string("metrics"), "move_and_cleaned_metric"}, std::to_string(get_metric()));

        }

        int get_metric(){ return code + child->get_metric(); }

        virtual void move_agent(std::string agent_name, point movement_vector) 
        {
            if(!(movement_vector == (point){0,0}))   
            {
                code--;
                Logger::save({std::string("metrics"), "move_and_cleaned_metric"}, std::to_string(get_metric()));
            }

            return child->move_agent(agent_name, movement_vector);
        }

        virtual bool add_agent(Agent* agent, point position) 
        {
            return child->add_agent(agent, position);
        }
        
        virtual bool clean(std::string agent_name, point relative_position)
        {
            auto res = child->clean(agent_name, relative_position);

            Logger::save({std::string("metrics"), "move_and_cleaned_metric"}, std::to_string(get_metric()));

            return res;
        } 

        virtual ~MoveCleanedMetric() 
        {
            delete child;
        }

};