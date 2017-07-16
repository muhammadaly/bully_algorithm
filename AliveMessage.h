#ifndef ALIVEMESSAGE_H
#define ALIVEMESSAGE_H

#include "Message.h"
#include <time.h>
class AliveMessage : public Message
{
public:
    AliveMessage()
    {
        m_data = std::time(NULL);
    }
    AliveMessage(INT p_src_Id)
    {
        m_src  = p_src_Id ;
        m_data    = time(NULL);
    }
    time_t  m_data;
};

#endif // ALIVEMESSAGE_H
