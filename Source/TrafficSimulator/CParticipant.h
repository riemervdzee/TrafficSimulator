#ifndef CPARTICIPANT_H
#define CPARTICIPANT_H

#include "TrafficDefs.h"
#include "CTrafficLane.h"

class CParticipant
{
public:



private:
    TDWDEFS::PARTICIPANTS type;
    TDWDEFS::PARTICIPANTSTATE participantState;
    // Vector3 position;
    // matrix3 rotation;
    CTrafficLane *laneFrom;
    CTrafficLane *laneTo;
};

#endif // CPARTICIPANT_H
