#include "../cArbitrator.h"

#include "cBus.h"

using namespace std;
using namespace ARBIT;

// Constructor, pass the argument straight to iEvent
cBus::cBus( TRADEFS::SimulationQueueParticipant_t Event) : iEvent( Event) {}

// Empty deconstructor
cBus::~cBus() {}

// The score is based upon time only
void cBus::CalculateScore( int CurrentTime)
{
    _Score = CurrentTime - _TimeReceived;
}

// We can't combine busses, as their "TO" direction can be different.
bool cBus::AddEvent( TRADEFS::SimulationQueueParticipant_t Event)
{
    return false;
}

int cBus::ExecuteActionGreen  ( const cNetworkView *)
{
    //TODO send message

    return 0;
}

int cBus::ExecuteActionOrange ( const cNetworkView *)
{
    //TODO send message

    return 0;
}

bool cBus::ExecuteActionRed    ( const cNetworkView *)
{
    //TODO send message

    return true;
}
