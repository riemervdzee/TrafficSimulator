#include "../cArbitrator.h"

#include "cPedestrian.h"

using namespace std;
using namespace ARBIT;

// Constructor, pass the argument straight to iAction
cPedestrian::cPedestrian( TRADEFS::SimulationQueueParticipant_t Event) : iAction( Event) {}

// Empty deconstructor
cPedestrian::~cPedestrian() {}

// The score is based upon time only
int cPedestrian::CalculateScore( int CurrentTime)
{
    return CurrentTime - _TimeReceived;
}

// As we don't count the amount of pedestrians, return true always
bool cPedestrian::AddEvent( TRADEFS::SimulationQueueParticipant_t Event)
{
    return true;
}

int cPedestrian::ExecuteActionGreen ( cNetworkView *view)
{
    //TODO send message

    return 0;
}

int cPedestrian::ExecuteActionOrange ( cNetworkView *view)
{
    //TODO send message

    return 0;
}

bool cPedestrian::ExecuteActionRed ( cNetworkView *view)
{
    //TODO send message

    return true;
}
