#ifndef CTRAFFICLANE_H
#define CTRAFFICLANE_H

#include "TrafficDefs.h"
#include "Math/WildMath.h"

class CTrafficLane
{
public:
    void SetWayStart(const wmath::Vec3& start);
    void SetWayEnd(const wmath::Vec3& start);

private:
    wmath::Vec3 wayStart;
    wmath::Vec3 wayEnd;
};

#endif // CTRAFFICLANE_H
