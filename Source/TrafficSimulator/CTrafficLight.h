#ifndef CTRAFFICLIGHT_H
#define CTRAFFICLIGHT_H

#include "trafficDefs.h"
#include "Math/WildMath.h"

class CTrafficLight
{
    public:
        CTrafficLight();
        CTrafficLight(wmath::Vec3 pos);

    private:
        wmath::Vec3 position;
        TRADEFS::TRAFFICLIGHTSTATE lightState;
};

#endif // CTRAFFICLIGHT_H
