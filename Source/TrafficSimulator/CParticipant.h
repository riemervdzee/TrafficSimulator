#ifndef CPARTICIPANT_H
#define CPARTICIPANT_H

#include "TrafficDefs.h"
#include "CTrafficLane.h"

class CParticipant
{
public:



private:
    TRADEFS::PARTICIPANTS type;
    TRADEFS::PARTICIPANTSTATE participantState;
    CTrafficLane *laneFrom;
    CTrafficLane *laneTo;
};

#endif // CPARTICIPANT_H
