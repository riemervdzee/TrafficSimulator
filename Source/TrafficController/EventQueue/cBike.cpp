#include "../cArbitrator.h"

#include "cBike.h"

using namespace std;
using namespace ARBIT;

// Constructor, pass the argument straight to iEvent
cBike::cBike( TRADEFS::SimulationQueueParticipant_t Event) : iEvent( Event) {}

// Empty deconstructor
cBike::~cBike() {}

// The score is based upon time only
void cBike::CalculateScore( int CurrentTime)
{
    _Score = CurrentTime - _TimeReceived;
}

// As we don't count the amount of bikes, return true always
bool cBike::AddEvent( TRADEFS::SimulationQueueParticipant_t Event)
{
    return true;
}

int cBike::ExecuteActionGreen  ( const cNetworkView *)
{
    //TODO send message

    return 0;
}

int cBike::ExecuteActionOrange ( const cNetworkView *)
{
    //TODO send message

    return 0;
}

bool cBike::ExecuteActionRed    ( const cNetworkView *)
{
    //TODO send message

    return true;
}
