#ifndef CTRAFFICLANEGROUP_H
#define CTRAFFICLANEGROUP_H

#include "TrafficDefs.h"
#include "CTrafficLane.h"

class CTrafficLaneGroup
{
public:
    CTrafficLane& operator[](int index)
    {
        if( index >= 0 || index <8)
        {
            return lanes[index];
        }
    }

    SetDirectionType(DIRECTION dir){ dirType = dir; }

private:
    CTrafficLane lanes[8];
    DIRECTION dirType;
};

#endif // CTRAFFICLANEGROUP_H
