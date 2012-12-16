#include "../cArbitrator.h"

#include "cBike.h"

using namespace std;
using namespace ARBIT;

// Constructor, pass the argument straight to iAction
cBike::cBike( TRADEFS::SimulationQueueParticipant_t Event) : iAction( Event) {}

// Empty deconstructor
cBike::~cBike() {}

// The score is based upon time only
int cBike::CalculateScore( int CurrentTime)
{
    return CurrentTime - _TimeReceived;
}

// As we don't count the amount of bikes, return true always
bool cBike::AddEvent( TRADEFS::SimulationQueueParticipant_t Event)
{
    return true;
}

int cBike::ExecuteActionGreen ( cNetworkView *view)
{
    //TODO send message

    return 0;
}

int cBike::ExecuteActionOrange ( cNetworkView *view)
{
    //TODO send message

    return 0;
}

bool cBike::ExecuteActionRed ( cNetworkView *view)
{
    //TODO send message

    return true;
}
