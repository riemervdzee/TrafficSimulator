#include "CTrafficLaneGroup.h"
#include "CTrafficLane.h"

CTrafficLaneGroup::CTrafficLaneGroup()
{
    // init pedestrian lanes
    lanes[0] = new CPedestrianTrafficLane();
    lanes[7] = new CPedestrianTrafficLane();

    // init common lanes
    for(int i = 1; i < 7; ++i)
    {
        lanes[i] = new CCommonTrafficLane();
    }
}

CTrafficLaneGroup::~CTrafficLaneGroup()
{
    // free memory for the lanes
    for(int i = 0; i < 8; ++i)
    {
        delete lanes[i];
    }
}

CTrafficLane* CTrafficLaneGroup::operator[](int index)
{
    if( index >= 0 || index <8)
    {
        return lanes[index];
    }

    return 0;
}
