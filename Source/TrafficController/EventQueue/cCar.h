#ifndef CLASS_CAR_H
#define CLASS_CAR_H

#include "iAction.h"

class cNetworkView;

/*
 * Car class
 */
class cCar : public iAction
{
protected:
    // Constants
    static const int WAITTIME_GREEN   = 15;
    static const int WAITTIME_ORANGE  = 3;
    static const float SCORE_PRIORITY = 1;

    // We count the amount of cars on the lane
    int _Count;

public:
    // Virtual (de)constructor for inheritance
    cCar( TRADEFS::SimulationQueueParticipant_t Event);
    ~cCar();

    // Asks the event to add another event (same lane), returns true if succesfull
    // If returned false, a new iAction inherited obj will be created for the new event
    // For bikes, this is always true, counts the amount of cars in the queue
    bool AddEvent( TRADEFS::SimulationQueueParticipant_t Event);

    // Calculates the current score of the event based on the current Time
    int CalculateScore( int CurrentTime);

    // Let the event control the TrafficLights, returns the time required for the next state-change
    int  ExecuteActionGreen  ( cNetworkView *);
    int  ExecuteActionOrange ( cNetworkView *);
    bool ExecuteActionRed    ( cNetworkView *);

};

#endif // CLASS_CAR_H
