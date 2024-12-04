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
    private:
        std::vector<std::vector<Floor>> mat;
        std::map<std::string, agent_info> agents;
        bool is_multiagent;
        std::set<Floor> prohibited_floors = {Floor::wall, Floor::agent, Floor::empty};

        void print()
        {
            for(auto & v : mat)
            {
                for( auto f : v)
                    std::cout << (char)f;
                std::cout << std::endl;
            }
        }

        bool check(point position)
        {
            return mat.size() > position.y and 0<= position.y and
                position.x >= 0 and mat[0].size() > position.x;  
        }

    public:
        // Environment(std::string path, bool is_multiagent = false);
        Environment(std::vector<std::vector<Floor>> mat, bool is_multiagent = false)
        {
            this->mat = mat;
            this->is_multiagent = is_multiagent;
        }
        ~Environment()
        {
            for(auto [agent, info] : agents)
                delete info.ptr;
        }

        void move_agent(std::string agent_name, point movement_vector)
        {
            sleep(1);

            agent_info & agent = agents[agent_name];

            if(movement_vector == (point){0,0})
            {

                agent.ptr->get_sensor_manager()->add_event({
                                                        agents[agent.ptr->get_name()].floor_underneath, 
                                                        {0,0}
                                                    }
                                                );

                print();
                return;
            }


            std::cout << "1" << std::endl;
            point real_position = agents[agent_name].position + movement_vector;
            std::cout << "2" << std::endl;


            // std::cout << mat.size() << ' ' << mat[0].size() << std::endl <<

            Floor f = check(real_position) ? mat[real_position.y][real_position.x] : Floor::empty; 


            agent.ptr->get_sensor_manager()->add_event({
                                            f, 
                                            movement_vector
                                        }
                                );

            std::cout << "3" << std::endl;


            if( !check(real_position) or prohibited_floors.count(mat[real_position.y][real_position.x]) )
            {
                agent.ptr->get_sensor_manager()->add_event({
                                            agent.floor_underneath, 
                                            movement_vector * -1
                                        }
                                    );

                std::cout << "entrou no if" << std::endl;
                
            }

            else
            {
                std::cout << "entrou no else" << std::endl;

                mat[agent.position.y][agent.position.x] = agent.floor_underneath;
                agent.position = real_position;
                agent.floor_underneath = mat[agent.position.y][agent.position.x];
                mat[agent.position.y][agent.position.x] = Floor::agent;
            }

            print();

        }

        bool add_agent(Agent* agent, point position)
        {
            if (
                (!is_multiagent and agents.size() == 1) or
                !check(position) or 
                prohibited_floors.count(mat[position.y][position.x]) or
                agents.count(agent->get_name())
               )
                return false;

            agents[agent->get_name()] = {
                                        agent, 
                                        position, 
                                        mat[position.y][position.x]
                                        };

            mat[position.y][position.x] = Floor::agent;

            agent->get_sensor_manager()->add_event({
                                                        agents[agent->get_name()].floor_underneath, 
                                                        {0,0}
                                                    }
                                                );
            return true;
        }
        
        void clean(std::string agent_name, point relative_position)
        {
            sleep(1);
            
            if(relative_position == (point){0,0})
            {
                agents[agent_name].floor_underneath = Floor::clean;

                agents[agent_name].ptr->get_sensor_manager()->add_event({
                                            agents[agent_name].floor_underneath, 
                                            {0,0}
                                        }
                                    );

                print();

                return;
            }

            point real_position = agents[agent_name].position + relative_position;
            
            // Floor floor;
            // point delta_pos;

            if(!check(real_position))
            {
                agents[agent_name].ptr->get_sensor_manager()->add_event(
                    {
                        Floor::empty,
                        {0,0}
                    }
                );

                print();

                return;
            }

            if (
                !prohibited_floors.count(mat[real_position.y][real_position.x])
            )
                mat[real_position.y][real_position.x] = Floor::clean;
        
            agents[agent_name].ptr->get_sensor_manager()->add_event(
                {
                    mat[real_position.y][real_position.x],
                    {0,0}
                }
            );

            print();
        }

};
