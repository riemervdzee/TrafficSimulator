#ifndef CTRAFFICLIGHT_H
#define CTRAFFICLIGHT_H

#include "TrafficDefs.h"
#include "Math/WildMath.h"

class CTrafficLight
{
    public:
        CTrafficLight();
        CTrafficLight(wmath::Vec3 pos);
        TRADEFS::TRAFFICLIGHTSTATE GetState() {return lightState;}
        void SetState(TRADEFS::TRAFFICLIGHTSTATE state){ lightState = state;}

    private:
        wmath::Vec3 position;
        TRADEFS::TRAFFICLIGHTSTATE lightState;
};

#endif // CTRAFFICLIGHT_H
