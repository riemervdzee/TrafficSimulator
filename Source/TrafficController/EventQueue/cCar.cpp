#include "../cArbitrator.h"
#include "../PacketMaster.h"
#include "../cNetworkView.h"

#include "cCar.h"

using namespace std;
using namespace ARBIT;

// Constructor, pass the argument straight to iAction
cCar::cCar( TRADEFS::SimulationQueueParticipant_t Event) : iAction( Event) {}

// Empty deconstructor
cCar::~cCar() {}

// The score is based upon time only
int cCar::CalculateScore( int CurrentTime)
{
    return CurrentTime - _TimeReceived;
}

// We can combine Car events, huraay
bool cCar::AddEvent( TRADEFS::SimulationQueueParticipant_t Event)
{
    // TODO increase/decrease counter
    return true;
}

int cCar::ExecuteActionGreen ( cNetworkView *view)
{
    view->Send(
        PacketMaster::GetTraLightPackage(
            _FromDirection,
            _FromLane,
            TRADEFS::PROCEED
        )
    );

    // TODO we could base this on the amount of cars
    return WAITTIME_GREEN;
}

int cCar::ExecuteActionOrange ( cNetworkView *view)
{
    view->Send(
        PacketMaster::GetTraLightPackage(
            _FromDirection,
            _FromLane,
            TRADEFS::STOP_ALMOST
        )
    );

    return WAITTIME_ORANGE;
}

bool cCar::ExecuteActionRed ( cNetworkView *view)
{
    view->Send(
        PacketMaster::GetTraLightPackage(
            _FromDirection,
            _FromLane,
            TRADEFS::STOP
        )
    );

    // TODO base this on our counter
    return true;
}
