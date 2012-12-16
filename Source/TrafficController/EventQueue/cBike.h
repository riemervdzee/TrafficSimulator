#ifndef CLASS_BIKE_H
#define CLASS_BIKE_H

#include "iAction.h"

class cNetworkView;

/*
 * Bike class
 */
class cBike : public iAction
{
protected:
    // Constants
    static const int WAITTIME_GREEN   = 15;
    static const float SCORE_PRIORITY = 0.7;

public:
    // Virtual (de)constructor for inheritance
    cBike( TRADEFS::SimulationQueueParticipant_t Event);
    ~cBike();

    // Calculates the current score of the event based on the current Time
    int CalculateScore( int CurrentTime);

    // Asks the event to add another event (same lane), returns true if succesfull
    // If returned false, a new iAction inherited obj will be created for the new event
    // For bikes, this is always true, no counting either..
    bool AddEvent( TRADEFS::SimulationQueueParticipant_t Event);

    // Let the event control the TrafficLights, returns the time required for the next state-change
    int  ExecuteActionGreen  ( cNetworkView *);
    int  ExecuteActionOrange ( cNetworkView *);
    bool ExecuteActionRed    ( cNetworkView *);

};

#endif // CLASS_BIKE_H
