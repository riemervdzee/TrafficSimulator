#include "CParticipant.h"
#include <cstdio>

CParticipant::CParticipant(TRADEFS::PARTICIPANTS type, int from, int to, int lane, wmath::Vec3 pos, float rot)
{
    remove = false;
    hidden = true;
    this->type = type;
    laneGroupFrom = from;
    laneGroupTo = to;
    laneFrom = lane;
    position = pos;
    rotation = rot;
}
