#include <vector>
#include <algorithm>
#include <iostream>

#include "PacketMaster.h"
#include "cNetworkView.h"
#include "cArbitrator.h"
#include "EventQueue/cActionGroup.h"
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
    for(int i = 0; i < TRADEFS::MAXGROUPS; i++)
        for(int j = 0; j < MAXLANES_CONTROLLER; j++)
            ClearLane( i, j);
}

/**
 * Constructor
 */
cArbitrator::cArbitrator() : _CurrentEventGroup( NULL), _NextLightState( ARBIT::GREEN), _TimeNextEvent( 0)
{
    // We start with an empty cache
    FlushCache();
}

/**
 * Send to the client that all lights should be red
 */
void cArbitrator::EventConnectionEstablished( iNetworkObserver *view)
{
    // Debug
    //cout << "[debug]EventConnectionEstablished: Check if this function is actually called" << endl;

    // For every possible TrafficLight, put them on RED
    for(int dir = 0; dir < TRADEFS::MAXGROUPS; dir++)
        for(int lane = 0; lane < MAXLANES_CONTROLLER; lane++)
            if( lane != 6) /* Filter lane 6, as that is an exit */
                view->Send( PacketMaster::GetTraLightPackage( dir, lane, TRADEFS::STOP) );
}

/**
 * Basically reset the cArbitrator object
 */
void cArbitrator::EventConnectionLost()
{
    // Debug
    //cout << "[debug]EventConnectionLost: Check if this function is actually called" << endl;

    // Go through the queue and remove every object
    for ( vector<cActionGroup*>::iterator i = _Queue.begin(); i != _Queue.end(); i++)
    {
        (*i)->DeleteActions();
        delete (*i);
    }

    // Clears the queue and flush the cache
    _Queue.clear();
    FlushCache();

    // Reset the remaining variables (Same value as in constructor)
    _CurrentEventGroup = NULL;
    _NextLightState    = ARBIT::GREEN;
    _TimeNextEvent     = 0;
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
                for ( vector<cActionGroup*>::iterator i = _Queue.begin(); i != _Queue.end(); i++)
                    (*i)->CalculateScore( t);


                // Sort it and load up the first element
                sort ( _Queue.begin(), _Queue.end());
                _CurrentEventGroup = _Queue.at(0);

                // Execute the green function, get the time required for the next state change
                int val = _CurrentEventGroup->ExecuteActionGreen( this, (cNetworkView*) Observer);
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
                int val = _CurrentEventGroup->ExecuteActionOrange( this, (cNetworkView*) Observer);
                _TimeNextEvent = val + t;

                // Set the next Lightstate to Orange
                _NextLightState = ARBIT::RED;

                // Exception, some iAction implementers return 0 here, if this is true, just re-execute the current function
                if (val == 0)
                    Update( Observer, t);

                break;
            }

            case ARBIT::RED:
            {
                // Debug
                cout << "[arbit] Update: State is red" << endl;

                // Execute the red function
                bool ret = _CurrentEventGroup->ExecuteActionRed( this, (cNetworkView*) Observer, t);

                // If ret is true, we can remove the bloody thing
                if( ret)
                {
                    // Remove it from the queue
                    _Queue.erase (_Queue.begin());

                    // Delete the obj itself
                    delete _CurrentEventGroup;
                }

                // Re-execute the current function
                _NextLightState = ARBIT::GREEN;
                Update( Observer, t);

                break;
            }
        }
    }
}

/**
 * Adds a loop Event to the Arbitrator
 *
 * This function is two phased, First we try to add the event to any existing iAction or create a new one
 * The second is trying to find a suitable iActionGroup for the action, or create a new one
 */
void cArbitrator::AddEvent( SimulationQueueParticipant_t Event)
{
    // Check if there is any iAction for the current Event already (same direction/lane)
    iAction* lane = _LaneControls[ Event.fromDirection].lane[ Event.fromLane];

    //cout << "[arbit] AddEvent: EventType= " << Event.type << " , LaneControl= " << lane << endl;

    // Here our new iAction will be stored if neccesary
    iAction* obj = NULL;

    /**
     * This function is two phased, First we try to add the event to any existing iAction or create a new one
     * The second is trying to find a suitable iActionGroup for the action, or create a new one
     *
     * First phase!
     */

    // Switch on the type
    switch( Event.type)
    {
        // Is it a bike or participant? (handling them is quite similar)
        case TRADEFS::BIKE:
        case TRADEFS::PEDESTRIAN:
            // Is the lane empty?
            if( lane == NULL )
            {
                // Is the loop close?
                if( Event.loop == 0)
                {
                    // Only difference is the object itself of course
                    if( Event.type == TRADEFS::BIKE)
                        obj = new cBike( Event);
                    else
                        obj = new cPedestrian( Event);

                    // Push it and set the Lane to this iAction
                    _LaneControls[ Event.fromDirection].lane[ Event.fromLane] = obj;

                }
            }
            else
            {
                lane->AddEvent( Event);
            }

            break;

        // If it is a bus, always create a new event (never add to existing bus lanes)
        case TRADEFS::BUS:
            // Is the loop close?
            if( Event.loop == 0)
            {
                obj = new cBus( Event);
            }
            break;

        // Is it a car?
        case TRADEFS::CAR:
            // We only find close non-empty events important when there isn't an iAction on that lane yet
            if( lane == NULL)
            {
                // Check if it is a close-loop non-empty event then..
                // TODO this ain't working right with counting...
                if( Event.empty == false && Event.loop == 0)
                {
                    // Create a new iAction and set the Lane to this iAction
                    obj = new cCar( Event);
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

    /**
     * This function is two phased, First we try to add the event to any existing iAction or create a new one
     * The second is trying to find a suitable iActionGroup for the action, or create a new one
     *
     * Second phase!
     */

    // First check if we got an iAction anyway
    if( obj == NULL)
        return;

#if ACTIONGROUP_USE_GROUPS
    // Go through all ActionGroups to see if they can accept this new iAction
    bool result = false;

    for ( vector<cActionGroup*>::iterator i = _Queue.begin(); i != _Queue.end() && result == false; i++)
        result = (*i)->AddAction( obj);

    // If we failed to find a nice home for the iAction, create a new one
    if( result == false)
    {
        cActionGroup* ag = new cActionGroup( obj);
        _Queue.push_back ( ag);
    }

#else
    // Just create a single cActionGroup and add the iAction to it, and add the AG to the queue
    cActionGroup* ag = new cActionGroup( obj);
    _Queue.push_back ( ag);

#endif
}

/**
 * Clears a specific lane
 */
void cArbitrator::ClearLane( int LaneGroup, int Lane)
{
    _LaneControls[ LaneGroup ].lane[  Lane ] = NULL;
}
