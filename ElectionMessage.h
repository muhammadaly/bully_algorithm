#ifndef ELECTIONMESSAGE_H
#define ELECTIONMESSAGE_H

#include "Message.h"

class ElectionMessage : public Message
{
public:
    ElectionMessage(INT p_src_Id,INT p_data)
    {
        m_src  = p_src_Id ;
        m_data    = p_data;
    }
    INT m_data;
};

#endif // ELECTIONMESSAGE_H
