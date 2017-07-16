#ifndef BULLYPROCESS_H
#define BULLYPROCESS_H
#include "StateMachine.h"
#include "thread"
#include "ElectionMessage.h"
#include "AliveMessage.h"
#include "time.h"

#define DURATION  1000000

//class BullyProcessData : public EventData
//{
//public:
//    INT id;
//};

class BullyProcess : public StateMachine
{
public:
    BullyProcess();
    void stop();
    void start();
    void updateElection(ElectionMessage);
    void updateAlive(AliveMessage);

private:
    INT m_Id;
    INT m_master_Id;
    std::thread m_thread;
    std::string m_q_name;
    std::time_t m_last_time;
    bool m_stop;

    // State enumeration order must match the order of state method entries
    // in the state map.
    enum States
    {
        ST_START,
        ST_IDLE,
        ST_ELECTION,
        ST_STOP,
        ST_MAX_STATES
    };

    // Define the state machine state functions with event data type
    STATE_DECLARE(BullyProcess, Start, NoEventData)
    STATE_DECLARE(BullyProcess, Idle, NoEventData)
    STATE_DECLARE(BullyProcess, Election, NoEventData)
    STATE_DECLARE(BullyProcess, Stop, NoEventData)

    // State map to define state object order. Each state map entry defines a
    // state object.
    BEGIN_STATE_MAP
        STATE_MAP_ENTRY(&Start)
        STATE_MAP_ENTRY(&Idle)
        STATE_MAP_ENTRY(&Election)
        STATE_MAP_ENTRY(&Stop)
    END_STATE_MAP

    void startListen();
    bool AmITheMaster(){return ( m_master_Id == m_Id);}
};


#endif // BULLYPROCESS_H
