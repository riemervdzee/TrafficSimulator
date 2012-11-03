#include "CTrafficLight.h"
CTrafficLight::CTrafficLight()
{
    position.x = 0;
    position.y = 0;
    position.z = 0;
    lightState = TRADEFS::PROCEED;
}

CTrafficLight::CTrafficLight(wmath::Vec3 pos)
{
    position = pos;
    lightState = TRADEFS::PROCEED;
}
