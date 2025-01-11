#pragma once
#include "agent.h"
#include "environment.h"
#include "concrete/dirt_sensor.h"
#include "concrete/cleaner_actuator.h"
#include "concrete/movement_actuator.h"
#include "concrete/collision_sensor.h"
#include <cstdlib>
#include <algorithm>

#include "logger.h"

class SmartAgent : public Agent
{
    private:
        int qtd = 0;

        std::vector<point> movements = {
            {1, 0},
            {0, 1},
            {-1, 0},
            {0, -1}
        };

        point current_pos = {0,0};
        point last_move = {0,0};

        std::vector<point> path;

        enum class AFloor : char{
            passed = 'p',
            unpassable = '#',
            unknown = '?'
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

        void print_model()
        {
            if(grid.size() == 0)
                return;

            std::string content = "";

            content += "model of " + this->get_name() + "\n\n";


            int small_x = 1e7, small_y = 1e7, big_x = -1e7, big_y = -1e7;

            for(auto [y, child] : grid)
            {
                big_y = std::max(big_y, y);
                small_y = std::min(small_y, y);

                for(auto [x, value] : child)
                {
                    big_x = std::max(big_x, x);
                    small_x = std::min(small_x, x);
                }
            }

            for(int y = small_y; y <= big_y; y++)
            {
                for(int x = small_x; x <= big_x; x++)
                {
                    if(grid[y].count(x))
                        content += (char)grid[y][x]; 
                    else
                        content += ' ';
                }

                content += '\n';
            }

            Logger::save("agent_intern_state", content + "\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n", true);

        }

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

                if((visited.count(pos.y) && visited[pos.y].count(pos.x)) || grid[pos.y][pos.x] == AFloor::unpassable)
                {
                    continue;
                }

                visited[pos.y][pos.x] = from;
                
                if(grid[pos.y][pos.x] == AFloor::unknown)
                {
                    ans = new point();
                    *ans = pos; 
                    break;
                }

                for (auto move : movements)
                    order.push({(pos + move), move});
            
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
            print_model();

            Logger::save("reasons_qtd", std::to_string(++qtd));

            int tzr = 0;

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


            if(path.size() == 0)
            {

                path = gen_route();
                if(path.size() == 0)
                {
                    this->cleaned_all = true;
                    return;
                }

                
            }

            auto m = path.back();
            path.pop_back();

            instruction i = {m};
            actuaors["move"]->act(&i);

            current_pos = current_pos + m;

            last_move = m;

        }

};