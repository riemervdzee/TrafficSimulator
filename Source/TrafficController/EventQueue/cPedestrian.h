#ifndef CLASS_PEDESTRIAN_H
#define CLASS_PEDESTRIAN_H

#include "iAction.h"

class cNetworkView;

/*
 * Pedestrian class
 */
class cPedestrian : public iAction
{
public:
    // Virtual (de)constructor for inheritance
    cPedestrian( TRADEFS::SimulationQueueParticipant_t Event);
    ~cPedestrian();

    // Asks the event to add another event (same lane), returns true if succesfull
    // If returned false, a new iAction inherited obj will be created for the new event
    // For pedestrians, this is always true, no counting either..
    bool AddEvent( TRADEFS::SimulationQueueParticipant_t Event);

    // Calculates the current score of the event based on the current Time
    void CalculateScore( int CurrentTime);

    // Let the event control the TrafficLights, returns the time required for the next state-change
    int  ExecuteActionGreen  ( cNetworkView *);
    int  ExecuteActionOrange ( cNetworkView *);
    bool ExecuteActionRed    ( cNetworkView *);

};

#endif // CLASS_PEDESTRIAN_H
