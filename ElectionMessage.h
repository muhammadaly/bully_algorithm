#ifndef ELECTIONMESSAGE_H
#define ELECTIONMESSAGE_H

#include "Message.h"

class ElectionMessage : public Message
{
public:
    ElectionMessage();
    ElectionMessage(INT p_src_Id,INT p_data)
    {
        m_src  = p_src_Id ;
        m_dst = -1;
        m_data    = p_data;
    }
private:
    INT m_data;
};

#endif // ELECTIONMESSAGE_H
