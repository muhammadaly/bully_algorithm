#include "MessageRouter.h"

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
        thread->updateElection(p_election_msg);
}
bool MessageRouter::broadAliveMessage(AliveMessage p_alive_msg)
{
    for(auto thread : threadPool)
        thread->updateAlive(p_alive_msg);
}
