#ifndef CTRAFFICLIGHT_H
#define CTRAFFICLIGHT_H

#include "trafficDefs.h"
#include "Math/WildMath.h"

class CTrafficLight
{
    public:
        CTrafficLight();
        virtual ~CTrafficLight();

        void SetPos(wmath::Vec3 pos)
        {
            position = pos;
        }

    private:
        wmath::Vec3 position;
        TRAFFICLIGHTSTATE lightState;
};

#endif // CTRAFFICLIGHT_H
