#ifndef CTRAFFICLIGHT_H
#define CTRAFFICLIGHT_H

#include "Math/WildMath.h"

class CTrafficLight
{
    public:
        CTrafficLight();
        virtual ~CTrafficLight();

    private:
        wmath::Vec3 position;
};

#endif // CTRAFFICLIGHT_H
