#include <vector>

#include "cArbitrator.h"
#include "EventQueue/cBike.h"
#include "EventQueue/cBus.h"
#include "EventQueue/cCar.h"
#include "EventQueue/cPedestrian.h"
using namespace std;
using namespace ARBIT;
using namespace TRADEFS;

/**
 * Constructor
 */
cArbitrator::cArbitrator() : _CurrentEvent( NULL), _CurrentState( ARBIT::GREEN)
{
    // Set every lane to NULL
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 8; j++)
            _LaneControls[i].lane[8] = NULL;
}

/**
 *
 */
void cArbitrator::AddEvent( SimulationQueueParticipant_t Event)
{
    // Check if there is any iEvent for the current Event already (same direction/lane)
    iEvent* lane = _LaneControls[ Event.fromDirection].lane[ Event.fromLane];

    // Switch on the type
    switch( Event.type)
    {
        // Is it a bike or participant? (handling them is quite similar)
        case TRADEFS::BIKE:
        case TRADEFS::PARTICIPANTS:
            // Is the lane empty?
            if( lane == NULL)
            {
                // Create a new iEvent
                iEvent* obj;

                // Only difference is the object itself of course
                if( Event.type == TRADEFS::BIKE)
                    obj = new cBike( Event);
                else
                    obj = new CParticipant( Event);

                // Push it and set the Lane to this iEvent
                _Queue.push_back ( obj);
                _LaneControls[ Event.fromDirection].lane[ Event.fromLane] = obj;
            }
            else
            {
                lane->AddEvent( event);
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
 *
 */
void cArbitrator::Update( const iNetworkObserver*, int t)
{

}
