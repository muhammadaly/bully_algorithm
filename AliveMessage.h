#ifndef ALIVEMESSAGE_H
#define ALIVEMESSAGE_H

#include "Message.h"
#include <time.h>
class AliveMessage : public Message
{
public:
    AliveMessage()
    {
        m_src = -1;
        m_dst = -1;
    }
    AliveMessage(INT p_src_Id)
    {
        m_src  = p_src_Id ;
        m_dst = -1;
    }
};

#endif // ALIVEMESSAGE_H
