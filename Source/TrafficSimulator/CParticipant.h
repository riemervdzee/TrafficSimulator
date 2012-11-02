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
    CTrafficLane *laneFrom;
    CTrafficLane *laneTo;
};

#endif // CPARTICIPANT_H
