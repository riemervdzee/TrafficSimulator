#include "CTrafficLane.h"

void CTrafficLane::SetWayStart(const wmath::Vec3& start)
{
    wayStart = start;
}

void CTrafficLane::SetWayEnd(const wmath::Vec3& end)
{
    wayEnd = end;
}

void CTrafficLane::SetTrafficlight(CTrafficLight light)
{
    this->light = light;
}
