//#include "../cArbitrator.h"
#include "../TrafficDefs.h"

#include "iAction.h"

// Copy most basic variables from the Event package
iAction::iAction( TRADEFS::SimulationQueueParticipant_t Event)
{
    _Type          = Event.type;
    _TimeReceived  = Event.time;
    _FromDirection = Event.fromDirection;
    _ToDirection   = Event.toDirection;
    _FromLane      = Event.fromLane;
    _ToLane        = Event.toLane;
}

// As we have a constructor, all other functions need to be declared as well. Mostly bogus
iAction::~iAction() { }
int  iAction::CalculateScore      ( int CurrentTime) { return 0;}
bool iAction::AddEvent            ( TRADEFS::SimulationQueueParticipant_t Event) {return true;}
int  iAction::ExecuteActionGreen  ( cNetworkView *) { return 0;}
int  iAction::ExecuteActionOrange ( cNetworkView *) { return 0;}
bool iAction::ExecuteActionRed    ( cNetworkView *) { return true;}
