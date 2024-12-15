#include<iostream>
#include<thread>
#include <semaphore>
#include "agent.h"
#include "environment.h"
#include "concrete/dummy_agent.h"
#include "concrete/smart_agent.h"
#include "concrete/concrete_environment.h"
#include "concrete/metrics/move_cleaned_metric.h"


using std::cout, std::endl;

int main(int argc, char **argv)
{
    MoveCleanedMetric env = new MoveCleanedMetric(
                                    new ConcreteEnvironment(std::string(argv[1]))
                                    );

    Agent * a = new SmartAgent(&env,"rogerio");

    env.add_agent_randomly(a);

    a->run();

    a->join();

    return 0;
}
