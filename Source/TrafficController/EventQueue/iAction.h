#ifndef INTERFACE_EVENT_H
#define INTERFACE_EVENT_H

#include "../TrafficDefs.h"

class cNetworkView;

/*
 * Standard interface class for events
 */
class iAction
{
protected:
    // What kind of Participant caused the event (filled by iAction constructor)
    TRADEFS::PARTICIPANTS _Type;

    // The TC time of when the event was generated (filled by iAction constructor)
    int _TimeReceived;

    // Basic direction variables (filled by iAction constructor)
    TRADEFS::DIRECTION _FromDirection;
    TRADEFS::DIRECTION _ToDirection;
    int _FromLane;
    int _ToLane;

public:
    // Standard constructor to fill in the most basic variables
    iAction( TRADEFS::SimulationQueueParticipant_t Event);

    // Virtual deconstructor for inheritance
    virtual ~iAction();

    // Reset the timereceived on this package
    inline void ResetTime( int time) { _TimeReceived = time;}

    // A few getters
    inline TRADEFS::PARTICIPANTS getType()          { return _Type;}
    inline TRADEFS::DIRECTION    getFromDirection() { return _FromDirection;}
    inline int                   getFromLane()      { return _FromLane;}

    // Calculates the current score of the event based on the current Time
    virtual int CalculateScore( int CurrentTime);

    // Asks the iAction obj to add another event (same lane), returns true if succesful
    // If returned false, a new iAction inherited obj will be created for the event
    virtual bool AddEvent( TRADEFS::SimulationQueueParticipant_t Event);

    // Let the event control the TrafficLights, returns the time required for the next state-change
    virtual int ExecuteActionGreen  ( cNetworkView *);
    virtual int ExecuteActionOrange ( cNetworkView *);
    /* Returns whether all participants are gone (true) or not (false) */
    virtual bool ExecuteActionRed   ( cNetworkView *);

};

#endif // INTERFACE_EVENT_H
