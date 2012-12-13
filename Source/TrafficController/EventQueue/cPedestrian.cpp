#include "../cArbitrator.h"

#include "cPedestrian.h"

using namespace std;
using namespace ARBIT;

// Constructor, pass the argument straight to iEvent
cPedestrian::cPedestrian( TRADEFS::SimulationQueueParticipant_t Event) : iEvent( Event) {}

// Empty deconstructor
cPedestrian::~cPedestrian() {}

// The score is based upon time only
void cPedestrian::CalculateScore( int CurrentTime)
{
    _Score = CurrentTime - _TimeReceived;
}

// As we don't count the amount of pedestrians, return true always
bool cPedestrian::AddEvent( TRADEFS::SimulationQueueParticipant_t Event)
{
    return true;
}

int cPedestrian::ExecuteActionGreen  ( const cNetworkView *)
{
    //TODO send message

    return 0;
}

int cPedestrian::ExecuteActionOrange ( const cNetworkView *)
{
    //TODO send message

    return 0;
}

bool cPedestrian::ExecuteActionRed    ( const cNetworkView *)
{
    //TODO send message

    return true;
}
