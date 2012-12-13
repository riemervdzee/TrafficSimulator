//#include "../cArbitrator.h"
#include "../TrafficDefs.h"

#include "iEvent.h"

// Copy most basic variables from the Event package
iEvent::iEvent( TRADEFS::SimulationQueueParticipant_t Event)
{
    _Type          = Event.type;
    _TimeReceived  = Event.time;
    _FromDirection = Event.fromDirection;
    _ToDirection   = Event.toDirection;
    _FromLane      = Event.fromLane;
    _ToLane        = Event.toLane;
}

// As we have a constructor, all other functions need to be declared as well. Mostly bogus
iEvent::~iEvent() { }
void iEvent::CalculateScore      ( int CurrentTime) { }
bool iEvent::AddEvent            ( TRADEFS::SimulationQueueParticipant_t Event) {return true;}
int  iEvent::ExecuteActionGreen  ( cNetworkView *) { return 0;}
int  iEvent::ExecuteActionOrange ( cNetworkView *) { return 0;}
bool iEvent::ExecuteActionRed    ( cNetworkView *) { return true;}
