#include<iostream>
#include<thread>
#include <semaphore>
#include "agent.h"
#include "environment.h"
#include "concrete/dummy_agent.h"
#include "concrete/smart_agent.h"

using std::cout, std::endl;

int main()
{
    Environment env(
        {
            {Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty},
            {Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty},
            {Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty},
            {Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty},
            {Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty},
            {Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty},
            {Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty,Floor::dirty}
        }, true
    );

    Agent * a = new SmartAgent(&env,"rogerio");

    env.add_agent(a, {0,0});

    a->run();

    cout << "Merda bosta" << endl;
    a->join();

    return 0;
}