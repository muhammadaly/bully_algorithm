#include "BullyProcess.h"
#include "IdsGenerator.h"
#include <iostream>
#include <time.h>

BullyProcess::BullyProcess():
    StateMachine(ST_MAX_STATES)
{
    m_Id = IdsGenerator::getInstance()->getUniqueId();
    m_master_Id = m_Id;
    m_q_name = "q#" + std::to_string(m_Id);
}

void BullyProcess::stop()
{
    BEGIN_TRANSITION_MAP                                               // - Current State -
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                           // ST_START
        TRANSITION_MAP_ENTRY (ST_STOP)                                 // ST_IDLE
        TRANSITION_MAP_ENTRY (ST_STOP)                                 // ST_ELECTION
        TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)                           // ST_STOP
    END_TRANSITION_MAP(NULL)
}

void BullyProcess::start()
{
    m_thread = std::thread(&BullyProcess::Idle,this);
    BEGIN_TRANSITION_MAP                                               // - Current State -
        TRANSITION_MAP_ENTRY (ST_IDLE)                                 // ST_START
        TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)                           // ST_IDLE
        TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)                           // ST_ELECTION
        TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)                           // ST_STOP
    END_TRANSITION_MAP(NULL)
}

void BullyProcess::updateElection(ElectionMessage msg)
{
    if(msg.m_data > m_master_Id)
        m_master_Id = msg.m_data;
    BEGIN_TRANSITION_MAP                                               // - Current State -
        TRANSITION_MAP_ENTRY (ST_ELECTION)                             // ST_START
        TRANSITION_MAP_ENTRY (ST_ELECTION)                             // ST_IDLE
        TRANSITION_MAP_ENTRY (ST_ELECTION)                             // ST_ELECTION
        TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)                           // ST_STOP
    END_TRANSITION_MAP(NULL)
}

void BullyProcess::updateAlive(AliveMessage msg)
{
    BEGIN_TRANSITION_MAP                                           // - Current State -
        TRANSITION_MAP_ENTRY (ST_IDLE)                             // ST_START
        TRANSITION_MAP_ENTRY (ST_IDLE)                             // ST_IDLE
        TRANSITION_MAP_ENTRY (ST_IDLE)                             // ST_ELECTION
        TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)                       // ST_STOP
    END_TRANSITION_MAP(NULL)
}

STATE_DEFINE(BullyProcess, Start, NoEventData)
{
    std::cout << "Starting .. " << std::endl;
}

STATE_DEFINE(BullyProcess, Stop, NoEventData)
{
    if(m_thread.joinable()) m_thread.join();
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
    m_master_Id = m_Id;
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
