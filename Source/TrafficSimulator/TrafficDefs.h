#ifndef TRAFFICDEFS_H
#define TRAFFICDEFS_H

namespace TRADEFS
{
    const float CARSIZE = 11.0f;
    const float BUSSIZE = 22.0f;
    const float BIKESIZE = 6.0f;
    const float PEDSIZE = 2.0f;

    const float CARSPEED = 16.0f;
    const float BUSSPEED = 7.0f;
    const float PEDSPEED = 2.0f;
    const float BIKESPEED = 4.0f;

    enum DIRECTION
    {
        NORTH = 0,
        SOUTH,
        EAST,
        WEST
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

};

#endif // TRAFFICDEFS_H
