#ifndef CTRAFFICLANE_H
#define CTRAFFICLANE_H

#include "TrafficDefs.h"
#include "CTrafficLight.h"
#include "Math/WildMath.h"

class CTrafficLane
{
public:
    CTrafficLane() : lightID(-1), partCount(0) {}
    void SetWayStart(const wmath::Vec3& start);
    void SetWayEnd(const wmath::Vec3& start);
    wmath::Vec3 GetWayStart() {return wayStart;}
    wmath::Vec3 GetWayEnd() {return wayEnd;}
    void SetTrafficlight(int light);
    int GetLightID(){ return lightID;}

    void IncCount() { partCount++; }
    void DecCount() { partCount++; }
    int GetParCount() { return partCount; }

private:
    wmath::Vec3 wayStart;
    wmath::Vec3 wayEnd;
    int lightID;
    int partCount;
};

#endif // CTRAFFICLANE_H
