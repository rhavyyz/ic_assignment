#include<iostream>
#include<thread>
#include <semaphore>
#include "agent.h"
#include "environment.h"
#include "concrete/dummy_agent.h"

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

    Agent * a = new DummyAgent(&env,"rogerio");
    Agent * b = new DummyAgent(&env,"rogerio2");

    env.add_agent(a, {0,0});
    env.add_agent(b, {3,3});

    a->run();

    cout << "Merda bosta" << endl;
    a->join();

    return 0;
}