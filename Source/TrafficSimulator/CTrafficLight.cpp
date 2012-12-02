#include "CTrafficLight.h"
CTrafficLight::CTrafficLight()
{
    position.x = 0;
    position.y = 0;
    position.z = 0;
    lightState = TRADEFS::PROCEED;
    rot = 0;
}

CTrafficLight::CTrafficLight(wmath::Vec3 pos, float rot)
{
    this->rot = rot;
    position = pos;
    lightState = TRADEFS::PROCEED;
}
