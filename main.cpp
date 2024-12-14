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

int main()
{
    MoveCleanedMetric env = new MoveCleanedMetric(new ConcreteEnvironment(
        {
            {Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty},
            {Floor::dirty,Floor::wall,Floor::wall,Floor::wall,Floor::wall,Floor::wall},
            {Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty},
            {Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty},
            {Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty},
            {Floor::dirty,Floor::dirty,Floor::dirty,Floor::wall,Floor::dirty,Floor::dirty},
            {Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty}
        }, true
    ));

    Agent * a = new SmartAgent(&env,"rogerio");

    env.add_agent(a, {0,0});

    a->run();

    a->join();

    return 0;
}
