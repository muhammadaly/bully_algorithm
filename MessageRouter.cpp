#include "MessageRouter.h"

MessageRouter *MessageRouter::getInstance()
{
    if(!instance)
        instance = new Message;
    return instance;
}

MessageRouter::MessageRouter()
{
    boost::interprocess::message_queue::remove(QName);
    m_queue = boost::interprocess::message_queue(boost::interprocess::open_or_create      //only create
            ,QName                                                                        //name
            ,1000                                                                         //max message number
            ,sizeof(Message));                                                            //max message size
}

bool MessageRouter::addNewMessage(Message msg)
{
    m_queue.send(&msg, sizeof(msg), 0);
}

bool MessageRouter::broadCastElectionMessage(ElectionMessage)
{

}
