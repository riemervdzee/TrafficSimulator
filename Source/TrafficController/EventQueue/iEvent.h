#ifndef INTERFACE_EVENT_H
#define INTERFACE_EVENT_H

#include "../TrafficDefs.h"

class cNetworkView;

/*
 * Standard interface class for events
 */
class iEvent
{
protected:
    // What kind of Participant caused the event (filled by iEvent constructor)
    TRADEFS::PARTICIPANTS _Type;

    // The TC time of when the event was generated (filled by iEvent constructor)
    int _TimeReceived;

    // Basic direction variables (filled by iEvent constructor)
    TRADEFS::DIRECTION _FromDirection;
    TRADEFS::DIRECTION _ToDirection;
    int _FromLane;
    int _ToLane;

    // Current "score" of the object, the higher the earlier processed
    int _Score;

public:
    // Standard constructor to fill in the most basic variables
    iEvent( TRADEFS::SimulationQueueParticipant_t Event);

    // Virtual deconstructor for inheritance
    virtual ~iEvent();

    // For sorting
    bool operator < ( const iEvent &a ) const {
        return  a._Score < _Score;
    }

    // Reset the timereceived on this package
    inline void ResetTime( int time) { _TimeReceived = time;}

    // Calculates the current score of the event based on the current Time
    virtual void CalculateScore( int CurrentTime);

    // Asks the event to add another event (same lane), returns true if succesfull
    // If returned false, a new iEvent inherited obj will be created for the new event
    virtual bool AddEvent( TRADEFS::SimulationQueueParticipant_t Event);

    // Let the event control the TrafficLights, returns the time required for the next state-change
    virtual int ExecuteActionGreen  ( cNetworkView *);
    virtual int ExecuteActionOrange ( cNetworkView *);
    /* Returns whether all participants are gone (true) or not (false) */
    virtual bool ExecuteActionRed   ( cNetworkView *);

};

#endif // INTERFACE_EVENT_H
