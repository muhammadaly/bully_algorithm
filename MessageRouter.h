#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <boost/interprocess/ipc/message_queue.hpp>
#include "ElectionMessage.h"
#include "BullyProcess.h"
#include "AliveMessage.h"

#define QName "message_pool"

class MessageRouter
{
public:
    static MessageRouter* getInstance();
    void attach(BullyProcess*);
    bool broadAliveMessage(AliveMessage p_alive_msg);
    bool broadCastElectionMessage(ElectionMessage p_election_msg);

private:
    static MessageRouter* instance;
    MessageRouter();
    std::vector<BullyProcess*> threadPool;
};

#endif // MESSAGEQUEUE_H
