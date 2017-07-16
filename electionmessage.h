#ifndef ELECTIONMESSAGE_H
#define ELECTIONMESSAGE_H

#include "Message.h"

class ElectionMessage : public Message
{
public:
    ElectionMessage();
    ElectionMessage(INT p_src_Id,INT p_dst_Id,INT p_data)
    {
        m_src  = p_src_Id ;
        m_dst = p_dst_Id;
        m_data    = p_data;
    }
private:
    INT m_data;
};

#endif // ELECTIONMESSAGE_H
