#include "CParticipant.h"

CParticipant::CParticipant(TRADEFS::PARTICIPANTS type, int from, int to, int lane, wmath::Vec3 pos, int parfront )
{
    remove = false;
    this->type = type;
    laneGroupFrom = from;
    laneGroupTo = to;
    laneFrom = lane;
    position = pos;
    parInFront = parfront;
}
