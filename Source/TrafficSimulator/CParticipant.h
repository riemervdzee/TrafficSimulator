#ifndef CPARTICIPANT_H
#define CPARTICIPANT_H

#include "TrafficDefs.h"
#include "Math/WildMath.h"

class CParticipant
{
    public:
        CParticipant(TRADEFS::PARTICIPANTS type, int from, int to, wmath::Vec3 pos );
        void SetState(TRADEFS::PARTICIPANTSTATE t) { state = t;}
        TRADEFS::PARTICIPANTSTATE GetState(){ return state; }
        TRADEFS::PARTICIPANTS GetType() { return type; }
        bool Remove(){ return remove;}
    private:
        TRADEFS::PARTICIPANTS type;
        TRADEFS::PARTICIPANTSTATE state;

        wmath::Vec3 position;
        int laneGroupFrom;
        int laneGroupTo;
        bool remove;
};

#endif // CPARTICIPANT_H
