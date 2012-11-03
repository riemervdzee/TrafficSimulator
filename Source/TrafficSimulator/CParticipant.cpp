#include "CParticipant.h"

CParticipant::CParticipant(TRADEFS::PARTICIPANTS type, int from, int to, wmath::Vec3 pos )
{
    remove = false;
    this->type = type;
    laneGroupFrom = from;
    laneGroupTo = to;
    position = pos;
}
