#include "../cArbitrator.h"

#include "cBus.h"

using namespace std;
using namespace ARBIT;

// Constructor, pass the argument straight to iAction
cBus::cBus( TRADEFS::SimulationQueueParticipant_t Event) : iAction( Event) {}

// Empty deconstructor
cBus::~cBus() {}

// The score is based upon time only
int cBus::CalculateScore( int CurrentTime)
{
    return CurrentTime - _TimeReceived;
}

// We can't combine busses, as their "TO" direction can be different.
bool cBus::AddEvent( TRADEFS::SimulationQueueParticipant_t Event)
{
    return false;
}

int cBus::ExecuteActionGreen ( cNetworkView *view)
{
    //TODO send message

    return 0;
}

int cBus::ExecuteActionOrange ( cNetworkView *view)
{
    //TODO send message

    return 0;
}

bool cBus::ExecuteActionRed ( cNetworkView *view)
{
    //TODO send message

    return true;
}
