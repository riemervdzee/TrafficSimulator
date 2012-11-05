#include "CTrafficLaneGroup.h"
#include "CTrafficLane.h"
#include <cstdio>

CTrafficLaneGroup::CTrafficLaneGroup()
{
    // init pedestrian lanes
    lanes[0] = new CPedestrianTrafficLane();
    lanes[TRADEFS::MAXLANES - 1] = new CPedestrianTrafficLane();

    // init common lanes
    for(int i = 1; i < 7; ++i)
    {
        lanes[i] = new CCommonTrafficLane();
    }
}

CTrafficLaneGroup::~CTrafficLaneGroup()
{
    // free memory for the lanes
    for(int i = 0; i < TRADEFS::MAXLANES; ++i)
    {
        delete lanes[i];
    }
}

CTrafficLane* CTrafficLaneGroup::operator[](int index)
{
    if( index >= 0 || index < TRADEFS::MAXLANES)
    {
        return lanes[index];
    }

    return 0;
}