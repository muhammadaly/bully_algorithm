#ifndef MESSAGE_H
#define MESSAGE_H

#include "DataTypes.h"

class Message{

public:
    Message(INT p_src,INT p_dst){
        m_src = p_src;
        m_dst = p_dst;
    }

protected:
        INT m_src,m_dst;
};

#endif // MESSAGE_H
