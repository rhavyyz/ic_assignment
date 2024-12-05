#pragma once
#include "agent.h"
#include "environment.h"
#include "concrete/dirt_sensor.h"
#include "concrete/cleaner_actuator.h"
#include "concrete/movement_actuator.h"
#include "concrete/collision_sensor.h"
#include <cstdlib>

class SmartAgent : public Agent
{
    private:
        std::vector<point> movements = {
            {1, 0},
            {0, 1},
            {-1, 0},
            {0, -1}
        };

        point current_pos = {0,0};
        point last_move = {0,0};

        std::vector<point> path;

        enum AFloor{
            passed = 0,
            unpassable = 1,
            unknown = 2
        };

        void set_unknown()
        {
            for(auto movement : movements)
            {
                auto p = current_pos + movement;
                if((!grid.count(p.y)) or (!grid[p.y].count(p.x)))
                    grid[p.y][p.x] = AFloor::unknown;
            }

            grid[current_pos.y][current_pos.x] = AFloor::passed;
        }

        std::map<int, std::map<int, AFloor>> grid;

        std::vector<point>gen_route()
        {
            std::map<int, std::map<int, point>> visited;
       
            std::queue<std::pair<point, point>> order;
            order.push(
                {current_pos, {-1000000, -1000000}}
            );


            point * ans = nullptr;


            while(!order.empty())
            {
                auto [pos, from] = order.front();
                order.pop();

                if(visited.count(pos.y) && visited[pos.y].count(pos.x) || grid[pos.y][pos.x] == AFloor::unpassable)
                    continue;

                visited[pos.y][pos.x] = from;
                
                if(grid[pos.y][pos.x] == AFloor::unknown)
                {

                    ans = new point();
                    *ans = pos; 
                }

                for (auto move : movements)
                    order.push({(current_pos + move), move});
            
            }

            if(ans == nullptr)
                return {};

            std::vector<point> res;


            while(true)
            {

                auto diff = visited[ans->y][ans->x];
                if(diff.x == -1000000)
                    break;
                res.push_back(diff);
                *ans = (*ans) + (diff*-1);
            }

            delete ans;
            return res;
        }

    public:
        SmartAgent(Environment * env, std::string name) : Agent(env, name)
        {
            this->actuaors = {
                    {"clean", (Actuator*) new CleanerActuator(env, name)}, 
                    {"move",  (Actuator*) new MovementActuator(env, name)}
                };

            this->sensors = new SensorManager(
                {
                    (Sensor *) new DirtSensor("dirt"),
                    (Sensor *) new CollisionSensor("col")
                }
            );

            grid[0][0] = AFloor::passed;
            
            grid[0][1] = AFloor::unknown;
            grid[0][-1] = AFloor::unknown;
            grid[-1][0] = AFloor::unknown;
            grid[1][0] = AFloor::unknown;

        }

        void reason(std::map<std::string, percept> perceptions)
        {
            int tzr = 0;
            std::cout << ++tzr << std::endl;


            if(perceptions["col"].code)
            {
                grid[current_pos.y][current_pos.x] = AFloor::unpassable;

                current_pos = current_pos + (last_move * -1);
                return;
            }

            set_unknown();            

            if(perceptions.count("dirt") && perceptions["dirt"].code )
            {
                actuaors["clean"]->act(NULL);
                return;
            }

            std::cout << ++tzr << std::endl;

            if(path.size() == 0)
            {
                std::cout <<"gen" << ++tzr << std::endl;

                path = gen_route();
                if(path.size() == 0)
                    std::terminate();

                std::cout <<"gen" << ++tzr << std::endl;
                
            }
            std::cout << ++tzr << std::endl;

            auto m = path.back();
            path.pop_back();
            std::cout << ++tzr << std::endl;

            instruction i = {m};
            actuaors["move"]->act(&i);
            std::cout << ++tzr << std::endl;

            current_pos = current_pos + m;

            last_move = m;
            std::cout << ++tzr << std::endl;

        }

};