#ifndef CLASS_BIKE_H
#define CLASS_BIKE_H

#include "iEvent.h"

class cNetworkView;

/*
 * Bike class
 */
class cBike : public iEvent
{
protected:
    // What kind of Participant caused the event
    /*TRADEFS::PARTICIPANTS _Type;

    // The TC time of when the event was generated
    int _TimeReceived;

    // Current "score" of the object, the higher the earlier
    int _Score;*/

public:
    // Virtual (de)constructor for inheritance
    inline cBike() { _Type = TRADEFS::BIKE;}
    ~cBike() {}

    // For sorting
    /*bool operator < ( const iEvent &a ) const {
        return  a._Score < _Score;
    }*/

    // Calculates the current score of the event based on the current Time
    void CalculateScore( int CurrentTime);

    // Let the event control the TrafficLights, returns the time required for the next state-change
    int ExecuteActionGreen  ( const cNetworkView *);
    int ExecuteActionOrange ( const cNetworkView *);
    int ExecuteActionRed    ( const cNetworkView *);

};

#endif // CLASS_BIKE_H
