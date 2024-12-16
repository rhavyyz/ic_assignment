#pragma once
#include "agent.h"
#include "environment.h"
#include "concrete/dirt_sensor.h"
#include "concrete/cleaner_actuator.h"
#include "concrete/movement_actuator.h"
#include <cstdlib>
#include "logger.h"

class DummyAgent : public Agent
{
    private:
        int qtd = 0;
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

            if (perceptions.size() == 0)
                return;
            
            Logger::save("reasons_qtd", std::to_string(++qtd));

            if(perceptions["dirt"].code == 1)
            {
                actuaors["clean"]->act(NULL);
                return;
            }

            srand(time(0)); 
            int movement = rand() % 4;

            std::vector<point> moves = {
                    {1, 0},
                    {-1, 0},
                    {0, 1},
                    {0, -1}
                };


            instruction ins = {
                moves[movement]
            };


            actuaors["move"]->act(&ins);
        }

};