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
    // What kind of Participant caused the event
    TRADEFS::PARTICIPANTS _Type;

    // The TC time of when the event was generated
    int _TimeReceived;

    // Current "score" of the object, the higher the earlier
    int _Score;

public:
    // Virtual (de)constructor for inheritance
    iEvent(): _Type( TRADEFS::CAR) {}
    virtual ~iEvent() {}

    // For sorting
    bool operator < ( const iEvent &a ) const {
        return  a._Score < _Score;
    }

    // Calculates the current score of the event based on the current Time
    virtual void CalculateScore( int CurrentTime);

    // Let the event control the TrafficLights, returns the time required for the next state-change
    virtual int ExecuteActionGreen  ( const cNetworkView *);
    virtual int ExecuteActionOrange ( const cNetworkView *);
    virtual int ExecuteActionRed    ( const cNetworkView *);

};

#endif // INTERFACE_EVENT_H
