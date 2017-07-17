#include "BullyProcess.h"
#include "IdsGenerator.h"
#include <time.h>
#include <unistd.h>
#include "MessageRouter.h"
#include <boost/interprocess/ipc/message_queue.hpp>
#include <iostream>
#include <vector>

BullyProcess::BullyProcess():
    StateMachine(ST_MAX_STATES)
{
    m_Id = IdsGenerator::getInstance()->getUniqueId();
    m_master_Id = -1;
    m_Eq_name = "q#" + std::to_string(m_Id)+"Election";
    m_Aq_name = "q#" + std::to_string(m_Id)+"Alive";
    m_stop = false;
    boost::interprocess::message_queue::remove(m_Eq_name.c_str());
    boost::interprocess::message_queue::remove(m_Aq_name.c_str());
    boost::interprocess::message_queue Emq (boost::interprocess::create_only
                                           ,m_Eq_name.c_str()
                                           ,100
                                           ,sizeof(ElectionMessage));
    boost::interprocess::message_queue Amq (boost::interprocess::create_only
                                           ,m_Aq_name.c_str()
                                           ,100
                                           ,sizeof(AliveMessage));
}

void BullyProcess::stop()
{
    m_stop = true;
    BEGIN_TRANSITION_MAP                                               // - Current State -
            TRANSITION_MAP_ENTRY (EVENT_IGNORED)                           // ST_START
            TRANSITION_MAP_ENTRY (ST_STOP)                                 // ST_IDLE
            TRANSITION_MAP_ENTRY (ST_STOP)                                 // ST_ELECTION
            TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)                           // ST_STOP
            END_TRANSITION_MAP(NULL)
}

void BullyProcess::start()
{
    //    m_thread = std::thread(&BullyProcess::Idle,this);
    BEGIN_TRANSITION_MAP                                               // - Current State -
            TRANSITION_MAP_ENTRY (ST_IDLE)                                 // ST_START
            TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)                           // ST_IDLE
            TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)                           // ST_ELECTION
            TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)                           // ST_STOP
            END_TRANSITION_MAP(NULL)
}

std::string BullyProcess::getElectionQName() const
{
    return m_Eq_name;
}
std::string BullyProcess::getAliveQName() const
{
    return m_Aq_name;
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
    if(AmITheMaster())
    {
        while(!m_stop)
        {
            AliveMessage m(m_Id);
            while(!MessageRouter::getInstance()->broadAliveMessage(m));
            usleep((unsigned int)DURATION);
        }
        InternalEvent(ST_STOP);
    }
    else
    {
        bool MasterAlive = true;
        do
        {
            std::cout << "I'm a live #" << std::to_string(m_Id) << std::endl;
            boost::interprocess::message_queue mq(
                        boost::interprocess::open_only,
                        m_Aq_name.c_str());
            boost::interprocess::message_queue::size_type recvd_size;
            AliveMessage msg;
            unsigned int priority;
            boost::posix_time::ptime timeout = boost::posix_time::microsec_clock::universal_time() +
                    boost::posix_time::milliseconds((double)DELAY);
            MasterAlive = mq.timed_receive(&msg, sizeof(msg), recvd_size, priority , timeout);
        }
        while(MasterAlive);
        InternalEvent(ST_ELECTION);
    }
}

STATE_DEFINE(BullyProcess, Election,NoEventData)
{
    //m_master_Id = m_Id;
    std::cout << "Election Start #" << std::endl;
    ElectionMessage s_msg(m_Id,m_Id);
    while(!MessageRouter::getInstance()->broadCastElectionMessage(s_msg));

    boost::interprocess::message_queue mq(
                boost::interprocess::open_only,
                m_Eq_name.c_str());
    boost::posix_time::ptime timeout = boost::posix_time::microsec_clock::universal_time() +
            boost::posix_time::milliseconds((double)WAITING_DELAY);
    int i = 0;
    while(i++ < 7)
    {
        boost::interprocess::message_queue::size_type recvd_size;
        ElectionMessage msg;
        unsigned int priority;
        if(mq.timed_receive(&msg, sizeof(msg), recvd_size, priority , timeout))
        {
            if(msg.m_data > m_master_Id)
                m_master_Id = msg.m_data;
        }
    }
    InternalEvent(ST_IDLE);
}
