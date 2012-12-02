#ifndef CTRAFFICLIGHT_H
#define CTRAFFICLIGHT_H

#include "TrafficDefs.h"
#include "Math/WildMath.h"

class CTrafficLight
{
    public:
        CTrafficLight();
        CTrafficLight(wmath::Vec3 pos, float rot);
        TRADEFS::TRAFFICLIGHTSTATE GetState() {return lightState;}
        void SetState(TRADEFS::TRAFFICLIGHTSTATE state){ lightState = state;}
        wmath::Vec3 GetPosition(){ return position; }
        void SetRotation(float rot){ this->rot = rot; }
        float GetRotation(){ return rot; }

    private:
        float rot;
        wmath::Vec3 position;
        TRADEFS::TRAFFICLIGHTSTATE lightState;
};

#endif // CTRAFFICLIGHT_H
