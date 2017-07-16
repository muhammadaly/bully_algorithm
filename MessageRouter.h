#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <boost/interprocess/ipc/message_queue.hpp>
#include "ElectionMessage.h"

#define QName "message_pool"

class MessageRouter
{
public:
    static MessageRouter* getInstance();
    bool addNewMessage(Message);
    bool broadCastElectionMessage(ElectionMessage);

private:
    static MessageRouter* instance;
    MessageRouter();

    boost::interprocess::message_queue m_queue;
};

#endif // MESSAGEQUEUE_H
