#ifndef CPARTICIPANT_H
#define CPARTICIPANT_H

#include "TrafficDefs.h"
#include "Math/WildMath.h"

class CParticipant
{
    public:
        CParticipant(TRADEFS::PARTICIPANTS type, int from, int to, int lane, wmath::Vec3 pos, int parfront);
        void SetState(TRADEFS::PARTICIPANTSTATE t) { state = t;}

        TRADEFS::PARTICIPANTSTATE   GetState(){ return state; }
        TRADEFS::PARTICIPANTS       GetType() { return type; }
        int GetFrom() const{ return laneGroupFrom; }
        int GetTo() const{ return laneGroupTo; }
        int GetLaneFrom() const{ return laneFrom; }
        wmath::Vec3 GetPosition() const { return position; }
        void SetPosition(wmath::Vec3 pos) { position = pos;}
        int GetParInFront() const{ return parInFront; }

        bool Remove(){ return remove;}
        void FlagForRemoval() { remove = true;}

    private:
        TRADEFS::PARTICIPANTS type;
        TRADEFS::PARTICIPANTSTATE state;

        wmath::Vec3 position;
        int laneGroupFrom;
        int laneGroupTo;
        int laneFrom;
        int parInFront;
        bool remove;
};

#endif // CPARTICIPANT_H
