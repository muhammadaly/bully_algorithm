#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H
#include <boost/lockfree/queue.hpp>
#include "Message.h"

class MessageQueue
{
public:
    MessageQueue();
    bool addNewMessage();

private:
    boost::lockfree::queue<Message> m_queue;
};

#endif // MESSAGEQUEUE_H
