#include "../PacketMaster.h"
#include "../cNetworkView.h"

#include "cBus.h"
using namespace std;

// Constructor, pass the argument straight to iAction
cBus::cBus( TRADEFS::SimulationQueueParticipant_t Event) : iAction( Event) {}

// Empty deconstructor
cBus::~cBus() {}

// The score is based upon time only
int cBus::CalculateScore( int CurrentTime)
{
    return (CurrentTime - _TimeReceived) * SCORE_PRIORITY;
}

// We can't combine busses, as their "TO" direction can be different.
bool cBus::AddEvent( TRADEFS::SimulationQueueParticipant_t Event)
{
    return false;
}

int cBus::ExecuteActionGreen ( cNetworkView *view)
{
    // TODO send message right message (Direction!)
    view->Send(
        PacketMaster::GetTraLightPackage(
            _FromDirection,
            _FromLane,
            TRADEFS::PROCEED
        )
    );

    return WAITTIME_GREEN;
}

int cBus::ExecuteActionOrange ( cNetworkView *view)
{
    // We got no Orange Command
    // note: we are cheating here a bit for busses, after 1 sec we turn the light to red, and wait another 3 secs.
    // This way we avoid that multiple busses drive upto the crossroad
    // Send message
    view->Send(
        PacketMaster::GetTraLightPackage(
            _FromDirection,
            _FromLane,
            TRADEFS::STOP
        )
    );
    return WAITTIME_ORANGE;
}

bool cBus::ExecuteActionRed ( cNetworkView *view)
{
    return true;
}
