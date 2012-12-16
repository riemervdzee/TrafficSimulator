#ifndef CLASS_BUS_H
#define CLASS_BUS_H

#include "iAction.h"

class cNetworkView;

/*
 * Bus class
 */
class cBus : public iAction
{
public:
    // Virtual (de)constructor for inheritance
    cBus( TRADEFS::SimulationQueueParticipant_t Event);
    ~cBus();

    // Calculates the current score of the event based on the current Time
    int CalculateScore( int CurrentTime);

    // Asks the event to add another event (same lane), returns true if succesfull
    // If returned false, a new iAction inherited obj will be created for the new event
    // For busses, this is always false!
    bool AddEvent( TRADEFS::SimulationQueueParticipant_t Event);

    // Let the event control the TrafficLights, returns the time required for the next state-change
    int  ExecuteActionGreen  ( cNetworkView *);
    int  ExecuteActionOrange ( cNetworkView *);
    bool ExecuteActionRed    ( cNetworkView *);

};

#endif // CLASS_BUS_H
