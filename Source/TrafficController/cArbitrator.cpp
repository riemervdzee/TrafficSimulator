#include <vector>
#include <algorithm>
#include <iostream>

#include "PacketMaster.h"
#include "cNetworkView.h"
#include "cArbitrator.h"
#include "EventQueue/cBike.h"
#include "EventQueue/cBus.h"
#include "EventQueue/cCar.h"
#include "EventQueue/cPedestrian.h"
using namespace std;
using namespace ARBIT;
using namespace TRADEFS;

/**
 * Clears the Cache
 */
void cArbitrator::FlushCache()
{
    // Set every lane to NULL
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 8; j++)
            _LaneControls[i].lane[j] = NULL;
}

/**
 * Constructor
 */
cArbitrator::cArbitrator() : _CurrentEvent( NULL), _NextLightState( ARBIT::GREEN), _TimeNextEvent( 0)
{
    // We start with an empty cache
    FlushCache();
}

/**
 * Send to the client that all lights should be red
 */
void cArbitrator::EventConnectionEstablished( iNetworkObserver *view)
{
    // TODO write this
    cout << "[debug]EventConnectionEstablished: Check if this function is actually called" << endl;

    // For every possible TrafficLight, put them on RED
    for(int dir = 0; dir < 4; dir++)
        for(int lane = 0; lane < 8; lane++)
            view->Send( PacketMaster::GetTraLightPackage( dir, lane, TRADEFS::STOP) );
}

/**
 * Basically reset the cArbitrator object
 */
void cArbitrator::EventConnectionLost()
{
    //cout << "[debug]EventConnectionLost: Check if this function is actually called" << endl;
    // Go through the queue and remove every object
    for ( vector<iEvent*>::iterator i = _Queue.begin(); i != _Queue.end(); i++)
        delete (*i);

    // Clears the queue and flush the cache
    _Queue.clear();
    FlushCache();

    // Reset the remaining variables (Same value as in constructor)
    _CurrentEvent   = NULL;
    _NextLightState = ARBIT::GREEN;
    _TimeNextEvent  = 0;
}

/**
 * Adds a loop Event to the Arbitrator
 */
void cArbitrator::AddEvent( SimulationQueueParticipant_t Event)
{
    // Check if there is any iEvent for the current Event already (same direction/lane)
    iEvent* lane = _LaneControls[ Event.fromDirection].lane[ Event.fromLane];

    //cout << "[arbit] AddEvent: EventType= " << Event.type << " , LaneControl= " << lane << endl;

    // Switch on the type
    switch( Event.type)
    {
        // Is it a bike or participant? (handling them is quite similar)
        case TRADEFS::BIKE:
        case TRADEFS::PEDESTRIAN:
            // Is the lane empty?
            if( lane == NULL)
            {
                // Create a new iEvent
                iEvent* obj;

                // Only difference is the object itself of course
                if( Event.type == TRADEFS::BIKE)
                    obj = new cBike( Event);
                else
                    obj = new cPedestrian( Event);

                // Push it and set the Lane to this iEvent
                _Queue.push_back ( obj);
                _LaneControls[ Event.fromDirection].lane[ Event.fromLane] = obj;
            }
            else
            {
                lane->AddEvent( Event);
            }

            break;

        // If it is a bus, always create a new event (never add to existing bus lanes)
        case TRADEFS::BUS:
            _Queue.push_back ( new cBus( Event));
            break;

        // Is it a car?
        case TRADEFS::CAR:
            // We only find close non-empty events important when there isn't an iEvent on that lane yet
            if( lane == NULL)
            {
                // Check if it is a close-loop non-empty event then..
                // TODO this ain't working..
                if( Event.empty == false && Event.loop == 0)
                {
                    // Create a new iEvent, push it and set the Lane to this iEvent
                    iEvent* obj = new cCar( Event);
                    _Queue.push_back ( obj);
                    _LaneControls[ Event.fromDirection].lane[ Event.fromLane] = obj;
                }
            }
            // Isn't the lane empty?
            else
            {
                // Check for close-loop empty=true event
                if( Event.empty == true && Event.loop == 0)
                {
                    lane->AddEvent( Event);
                }
                // Or for when a car approaches at the far-away loop.
                else if ( Event.empty == false && Event.loop == 1)
                {
                    lane->AddEvent( Event);
                }
            }

            break;

    }
}

/**
 * Update function
 */
void cArbitrator::Update( iNetworkObserver *Observer, int t)
{
    // Check if we even got events, and whether it is time or not
    if( _Queue.size() > 0 && _TimeNextEvent <= t)
    {
        //
        cout << "[arbit] Update: Time is up and queue size is " << _Queue.size() << endl;

        // Switch on what the next state will be
        switch( _NextLightState)
        {
            case ARBIT::GREEN:
            {
                // Debug
                cout << "[arbit] Update: State is green" << endl;

                // Go through all events, let them calculate the score
                for ( vector<iEvent*>::iterator i = _Queue.begin(); i != _Queue.end(); i++)
                    (*i)->CalculateScore( t);


                // Sort it and load up the first element
                sort ( _Queue.begin(), _Queue.end());
                _CurrentEvent = _Queue.at(0);

                // Execute the green function, get the time required for the next state change
                int val = _CurrentEvent->ExecuteActionGreen( (cNetworkView*) Observer);
                _TimeNextEvent = val + t;

                // Set the next Lightstate to Orange
                _NextLightState = ARBIT::ORANGE;

                break;
            }

            case ARBIT::ORANGE:
            {
                // Debug
                cout << "[arbit] Update: State is orange" << endl;

                // Orange is quite simple, just execute it and get to the choppah
                int val = _CurrentEvent->ExecuteActionOrange( (cNetworkView*) Observer);
                _TimeNextEvent = val + t;

                // Set the next Lightstate to Orange
                _NextLightState = ARBIT::RED;

                // Exception, some iEvent implementers return 0 here, if this is true, just re-execute the current function
                if (val == 0)
                    Update( Observer, t);
            }

            case ARBIT::RED:
            {
                // Debug
                cout << "[arbit] Update: State is red" << endl;

                // Execute the red function
                bool ret = _CurrentEvent->ExecuteActionRed( (cNetworkView*) Observer);

                // If ret is true, we can remove the bloody thing
                if( ret)
                {
                    // Reset the lane entry and remove it from the queue
                    _LaneControls[ _CurrentEvent->getFromDirection()].lane[ _CurrentEvent->getFromLane()] = NULL;
                    _Queue.erase (_Queue.begin());

                    // Delete the obj itself
                    delete _CurrentEvent;
                }
                else
                {
                    // Otherwise, reset the time
                    _CurrentEvent->ResetTime( t);
                }

                // Re-execute the current function
                _NextLightState = ARBIT::GREEN;
                Update( Observer, t);
            }
        }
    }
}
