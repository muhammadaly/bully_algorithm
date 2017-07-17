#include "ProcessFactory.h"
#include <iostream>
#include <thread>

void newProcess()
{
    ProcessFactory f;
    f.createNewProcess();
}
int main(int argc, char *argv[])
{
    std::vector<std::thread*> threads;
    for(int i = 0 ; i < 5 ; i ++)
    {
        std::thread* th = new std::thread(newProcess);
        th->join();
        threads.push_back(th);
//        threads[threads.size()-1].join();
    }

    int x ;
    std::cin >> x;
}
