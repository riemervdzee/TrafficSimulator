#include <iostream>
#include "../PacketMaster.h"
#include "../cNetworkView.h"

#include "cPedestrian.h"
using namespace std;

// Constructor, pass the argument straight to iAction
cPedestrian::cPedestrian( TRADEFS::SimulationQueueParticipant_t Event) : iAction( Event) {}

// Empty deconstructor
cPedestrian::~cPedestrian() {}

// The score is based upon time only
int cPedestrian::CalculateScore( int CurrentTime)
{
   return (CurrentTime - _TimeReceived) * SCORE_PRIORITY;
}

// As we don't count the amount of pedestrians, return true always
bool cPedestrian::AddEvent( TRADEFS::SimulationQueueParticipant_t Event)
{
    return true;
}

int cPedestrian::ExecuteActionGreen ( cNetworkView *view)
{
    // Some debug
    cout << "[PEDESTRIAN] Green! Dir " << _FromDirection << ", lane " << _FromLane << endl;

    // Send message
    view->Send(
        PacketMaster::GetTraLightPackage(
            _FromDirection,
            _FromLane,
            TRADEFS::PROCEED
        )
    );

    return WAITTIME_GREEN;
}

int cPedestrian::ExecuteActionOrange ( cNetworkView *view)
{
    // We got no Orange command
    // If the ActionGroup do has a time for Orange, the Pedestrian lane is simply longer open
    return 0;
}

bool cPedestrian::ExecuteActionRed ( cNetworkView *view)
{
    // Send stop command
    view->Send(
        PacketMaster::GetTraLightPackage(
            _FromDirection,
            _FromLane,
            TRADEFS::STOP
        )
    );

    // As we don't count pedestrians, we'll just assume everything is alrighty
    return true;
}
