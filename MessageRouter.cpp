#include "MessageRouter.h"
#include <boost/interprocess/ipc/message_queue.hpp>

MessageRouter* MessageRouter::instance = NULL;

MessageRouter *MessageRouter::getInstance()
{
    if(!instance)
        instance = new MessageRouter;
    return instance;
}

void MessageRouter::attach(BullyProcess * newThread)
{
    threadPool.push_back(newThread);
}

MessageRouter::MessageRouter()
{
    threadPool.clear();
}
bool MessageRouter::broadCastElectionMessage(ElectionMessage p_election_msg)
{
    for(auto thread : threadPool)
    {
        boost::interprocess::message_queue mq
                 (boost::interprocess::open_only
                 ,thread->getElectionQName().c_str()
                 );
        mq.send(&p_election_msg, sizeof(p_election_msg), 0);

    }
    return true;
}
bool MessageRouter::broadAliveMessage(AliveMessage p_alive_msg)
{
    for(auto thread : threadPool)
    {
        boost::interprocess::message_queue mq
                 (boost::interprocess::open_only
                 ,thread->getAliveQName().c_str()
                 );
        mq.send(&p_alive_msg, sizeof(p_alive_msg), 0);

    }
    return true;
}
