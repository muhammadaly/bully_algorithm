#include "BullyProcess.h"
#include "idsgenerator.h"
#include <iostream>
#include <time.h>

BullyProcess::BullyProcess():
    StateMachine(ST_MAX_STATES)
{
    m_Id = IdsGenerator::getInstance()->getUniqueId();
}

STATE_DEFINE(BullyProcess, Idle, NoEventData)
{
    bool MasterAlive = false;
    do
    {
        std::cout << "I'm a live #" << std::to_string(m_Id) << std::endl;
        MasterAlive = true;
    }
    while(MasterAlive);
    InternalEvent(ST_ELECTION);
}

STATE_DEFINE(BullyProcess, Election,NoEventData)
{
    master_Id = m_Id;
    // broadcast my_id
    startListen();

    InternalEvent(ST_IDLE);
}

void BullyProcess::startListen()
{
    time_t start, now;
    double seconds, wating_seconds = 1 * 60;
    time(&start);

    while(seconds < wating_seconds)
    {
        // wait for another ids
        // if received_id > current_master_id then current_master_id = received_id
        time(&now);
        seconds = difftime(start,now);
    }
}
