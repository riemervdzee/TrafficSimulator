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

    void SetDirectionType(int dir){ dirType = dir; }

private:
    CTrafficLane lanes[8];
    int dirType;
};

#endif // CTRAFFICLANEGROUP_H
