#pragma once
#include "agent.h"
#include "environment.h"
#include "concrete/dirt_sensor.h"
#include "concrete/cleaner_actuator.h"
#include "concrete/movement_actuator.h"
#include <cstdlib>

class DummyAgent : public Agent
{
    public:
        DummyAgent(Environment * env, std::string name) : Agent(env, name)
        {
            this->actuaors = {
                {"clean", (Actuator*) new CleanerActuator(env, name)}, 
                {"move",  (Actuator*) new MovementActuator(env, name)}
                };

            this->sensors = new SensorManager(
                {
                    (Sensor *) new DirtSensor("dirt")
                }
            );
        }

        void reason(std::map<std::string, percept> perceptions)
        {

            std::cout << "my_percerpts " <<perceptions.size() << std::endl; 

            if (perceptions.size() == 0)
                return;


            if(perceptions["dirt"].code == 1)
            {
                actuaors["clean"]->act(NULL);
                std::cout << "returned here \n";
                return;
            }

            int movement = rand() % 4;

            std::vector<point> moves = {
                    {1, 0},
                    {-1, 0},
                    {0, 1},
                    {0, -1}
                };


            std::cout << "before " << movement << std::endl;
            instruction ins = {
                moves[movement]
            };

            std::cout << "after" << std::endl;

            actuaors["move"]->act(&ins);
        }

};