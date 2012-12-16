#include <vector>
#include <algorithm>
#include <iostream>

#include "../cNetworkView.h"
#include "../cArbitrator.h"
#include "cActionGroup.h"
#include "iAction.h"
/*#include "cBike.h"
#include "cBus.h"
#include "cCar.h"
#include "cPedestrian.h"*/


/*
 * Use grouping part
 */
#if ACTIONGROUP_USE_GROUPS

// TODO TODO TODO etc.

/*
 * Don't use grouping, you bugger
 */
#else

// Constructor
cActionGroup::cActionGroup( iAction *action)
{
    _Actions = action;
}

// Reset the timereceived on the iAction object(s)
void cActionGroup::ResetTime( int time)
{
    _Actions->ResetTime( time);
}

// Calculates the current score of the event based on the current Time
void cActionGroup::CalculateScore( int CurrentTime)
{
    _Score = _Actions->CalculateScore( CurrentTime);
}

// Tries to add an Action to the current group, true=successful false=failure
bool cActionGroup::AddAction( iAction* action)
{
    // Always return false, as we don't have grouping
    return false;
}

// Remove any owned actions
void cActionGroup::DeleteActions()
{
    delete _Actions;
}

// Let the event control the TrafficLights, returns the time required for the next state-change
int cActionGroup::ExecuteActionGreen ( cArbitrator *arbi, cNetworkView *view)
{
    return _Actions->ExecuteActionGreen( view);
}

// Let the event control the TrafficLights, returns the time required for the next state-change
int cActionGroup::ExecuteActionOrange ( cArbitrator *arbi, cNetworkView *view)
{
    return _Actions->ExecuteActionOrange( view);
}

/* Returns whether all participants are gone (true) or not (false) */
bool cActionGroup::ExecuteActionRed ( cArbitrator *arbi, cNetworkView *view, int time)
{
    // Execute as normal
    bool ret = _Actions->ExecuteActionRed( view);

    // If ret is true, we can remove the bloody thing
    if( ret)
    {
        // Clears that lane
        arbi->ClearLane( _Actions->getFromDirection(),  _Actions->getFromLane());

        // Delete the obj itself
        delete _Actions;
    }
    else
    {
        // Otherwise, reset the time
        _Actions->ResetTime( time);
    }

    // Return the value
    return ret;
}

#endif
