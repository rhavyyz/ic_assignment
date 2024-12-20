#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>
#include "agent.h"
#include "floor.h"
#include "point.h"
#include "types.h"
#include "environment.h"

#include <unistd.h>
#include <fstream>
#include <algorithm>
#include <cstdlib>

#include"logger.h"


class ConcreteEnvironment : public Environment
{
    private:
        std::vector<std::vector<Floor>> mat;
        std::map<std::string, agent_info> agents;
        bool is_multiagent;
        std::set<Floor> prohibited_floors = {Floor::wall, Floor::agent, Floor::empty};

        void print()
        {

            std::string content = "";

            for(auto & v : mat)
            {
                for( auto f : v)
                        content +=  (char)f;
                content += "\n";
                
            }
            Logger::save("state_progression", content + "\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n", true);
        }

        bool check(point position)
        {
            return mat.size() > position.y and 0<= position.y and
                position.x >= 0 and mat[0].size() > position.x;  
        }

    public:
        // Environment(std::string path, bool is_multiagent = false);
        ConcreteEnvironment(std::vector<std::vector<Floor>> mat, bool is_multiagent = false)
        {
            this->mat = mat;
            this->is_multiagent = is_multiagent;
        }

        ConcreteEnvironment(std::string path, bool is_multiagent = false)
        {
            this->is_multiagent = is_multiagent;

            std::ifstream file(path);

            std::string s;

            int max_size = 0;

            while (getline(file, s))
            {

                std::vector<Floor> row;
                for(auto el : s)
                {
                    if(el != '\n')
                        row.push_back((Floor)(int)el);
                }

                mat.push_back(row);   
            
                max_size = std::max(max_size, (int)row.size());
            }

            for(auto & row : mat)
            {
                while(row.size() < max_size)
                    row.push_back(Floor::empty);
            }


        }

        virtual ~ConcreteEnvironment()
        {
            for(auto [agent, info] : agents)
                delete info.ptr;
        }

        void move_agent(std::string agent_name, point movement_vector)
        {
            // sleep(1);

            agent_info & agent = agents[agent_name];

            Logger::save("state_progression", 
                                std::string("Trying to move with vector ") + 
                                std::to_string(movement_vector.y) + 
                                ' ' + 
                                std::to_string(movement_vector.x) + 
                                '\n', 
                            true);


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

            point real_position = agents[agent_name].position + movement_vector;

            Floor f = check(real_position) ? mat[real_position.y][real_position.x] : Floor::empty; 


            agent.ptr->get_sensor_manager()->add_event({
                                            f, 
                                            movement_vector
                                        }
                                );

            if( !check(real_position) or prohibited_floors.count(mat[real_position.y][real_position.x]) )
            {
                agent.ptr->get_sensor_manager()->add_event({
                                            agent.floor_underneath, 
                                            movement_vector * -1
                                        }
                                    );

            }

            else
            {

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
        
        bool clean(std::string agent_name, point relative_position)
        {
            // sleep(1);
            
            point real_position = agents[agent_name].position + relative_position;

            // std::cout << "Cleaning at " << real_position.y << ' ' << real_position.x << std::endl;



            Logger::save("state_progression", 
                                std::string("Cleaning at ") + 
                                std::to_string( real_position.y) + 
                                ' ' + 
                                std::to_string(real_position.x) +
                                "\n"  
                               , 
                            true);

            bool cleaned = false;

            if(relative_position == (point){0,0})
            {
                if (agents[agent_name].floor_underneath == Floor::dirty)
                    cleaned = true;

                agents[agent_name].floor_underneath = Floor::clean; 
 
                agents[agent_name].ptr->get_sensor_manager()->add_event({ 
                                            agents[agent_name].floor_underneath, 
                                            {0,0} 
                                        }
                                    );

                print();

                return cleaned;
            }

            
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

                return false;
            }


            if (
                !prohibited_floors.count(mat[real_position.y][real_position.x])
            )
            {
                mat[real_position.y][real_position.x] = Floor::clean;
                cleaned = true;
            }
        
            agents[agent_name].ptr->get_sensor_manager()->add_event(
                {
                    mat[real_position.y][real_position.x],
                    {0,0}
                }
            );

            print();
            return cleaned;
        }

        bool add_agent_randomly(Agent* agent)
        {
            int x = mat[0].size(), y = mat.size();

            while(true) {
                srand(time(0)); 
                
                int curr_Y = rand()%y;
                srand(time(0)); 
                int curr_X = rand()%x;
            
                if(add_agent(agent, {curr_Y, curr_X}))
                    break;
            }

            return true;
        }
};
