#include "CParticipant.h"
#include <cstdio>

CParticipant::CParticipant(TRADEFS::PARTICIPANTS type, int from, int to, int lane, wmath::Vec3 pos)
{
    remove = false;
    hidden = false;
    this->type = type;
    laneGroupFrom = from;
    laneGroupTo = to;
    laneFrom = lane;
    position = pos;
}
