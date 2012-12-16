#include <iostream>
#include "../PacketMaster.h"
#include "../cNetworkView.h"

#include "cBike.h"
using namespace std;

// Constructor, pass the argument straight to iAction
cBike::cBike( TRADEFS::SimulationQueueParticipant_t Event) : iAction( Event) {}

// Empty deconstructor
cBike::~cBike() {}

// The score is based upon time only
int cBike::CalculateScore( int CurrentTime)
{
    return (CurrentTime - _TimeReceived) * SCORE_PRIORITY;
}

// As we don't count the amount of bikes, return true always
bool cBike::AddEvent( TRADEFS::SimulationQueueParticipant_t Event)
{
    return true;
}

int cBike::ExecuteActionGreen ( cNetworkView *view)
{
    // Some debug
    cout << "[BIKE] Green! Dir " << _FromDirection << ", lane " << _FromLane << endl;

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

int cBike::ExecuteActionOrange ( cNetworkView *view)
{
    // We got no Orange command
    // If the ActionGroup do has a time for Orange, the bike lane is simply longer open
    return 0;
}

bool cBike::ExecuteActionRed ( cNetworkView *view)
{
    // Send stop command
    view->Send(
        PacketMaster::GetTraLightPackage(
            _FromDirection,
            _FromLane,
            TRADEFS::STOP
        )
    );

    // As we don't count bikes, we just assume everything is alright
    return true;
}
