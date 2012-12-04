#ifndef TRAFFICDEFS_H
#define TRAFFICDEFS_H

/* Keep this in sync in both projects! */

namespace TRADEFS
{
    const int MAXGROUPS = 4;
    const int MAXLANES = 8;

    const float CARSIZE = 11.0f;
    const float BUSSIZE = 22.0f;
    const float BIKESIZE = 6.0f;
    const float PEDSIZE = 2.0f;

    const float CARSPEED = 8.0f;
    const float BUSSPEED = 6.5f;
    const float PEDSPEED = 10.0f;
    const float BIKESPEED = 4.0f;
    
    enum PEDTYPE
    {
        OTHER = 0,
        PED,
    };

    enum DIRECTION
    {
        NORTH = 0,
        SOUTH = 1,
        EAST = 2,
        WEST = 3
    };

    enum PARTICIPANTS
    {
        CAR = 0,
        BUS,
        BIKE,
        PEDESTRIAN
    };

    enum  PART_LANE
    {
        LANE_PEDESTRIAN_ONE = 0,
        LANE_EXIT = 6,
        LANE_BUS = 2,
        LANE_CAR_LEFT = 3,
        LANE_CAR_STRAIGHT = 4,
        LANE_CAR_RIGHT = 5,
        LANE_BIKE = 1,
        LANE_PEDESTRIAN_TWO = 7
    };

    enum TRAFFICLIGHTSTATE
    {
        PROCEED = 0,
        PROCEED_BLINKING,
        STOP,
        STOP_ALMOST,
        BUS_STRAIGHT,
        BUS_LEFT,
        BUS_RIGHT,
        BLINKING,
        OFF
    };

    enum PARTICIPANTSTATE
    {
        GOTOSTOPLIGHT = 0,
        WAITATSTOPLIGHT,
        ONCROSSROAD,
        GOTOEXIT
    };

    enum CONNECTIONSTATE
    {
        DOWN = 0,   // Socket ain't initialized yet / No connection
        LISTENING,  // Listening to connections
        CONNECTED,  // Connected
    };

    // data structure for the queue
    struct SimulationQueueParticipant_t
    {
        int time;
        TRADEFS::PARTICIPANTS type;
        TRADEFS::DIRECTION fromDirection;
        TRADEFS::DIRECTION toDirection;
        int fromLane;
        int toLane;

        bool operator < ( const SimulationQueueParticipant_t &a ) const {
            return  a.time < time;
        }
    };

};

#endif // TRAFFICDEFS_H
