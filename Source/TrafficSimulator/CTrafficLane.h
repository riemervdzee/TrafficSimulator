#ifndef CTRAFFICLANE_H
#define CTRAFFICLANE_H

#include "TrafficDefs.h"
#include "CTrafficLight.h"
#include "Math/WildMath.h"

class CTrafficLane
{
public:
    void SetWayStart(const wmath::Vec3& start);
    void SetWayEnd(const wmath::Vec3& start);
    void SetTrafficlight(CTrafficLight light);

private:
    wmath::Vec3 wayStart;
    wmath::Vec3 wayEnd;
    CTrafficLight light;
};

#endif // CTRAFFICLANE_H
