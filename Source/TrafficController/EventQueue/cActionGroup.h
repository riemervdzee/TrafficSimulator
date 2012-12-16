#ifndef CLASS_ACTIONGROUP_H
#define CLASS_ACTIONGROUP_H

#define ACTIONGROUP_USE_GROUPS 0

// Class prototype
class iAction;
class cArbitrator;
class cNetworkView;

/*
 * A collector of actions
 */
class cActionGroup
{
protected:
    // Current "score" of the iAction(s), the higher the earlier processed
    int _Score;

// If we want groups, get a vector of iAction objects
#if ACTIONGROUP_USE_GROUPS
    std::vector<iAction*> _Actions;
    // TODO probably more variables

// Otherwise, just have a single pointer
#else
    iAction* _Actions;
#endif

public:
    // For sorting
    bool operator < ( const cActionGroup &ag ) const {
        return  ag._Score < _Score;
    }

    // Reset the timereceived on the iAction object(s)
    void ResetTime( int time);

    // Calculates the current score of the event based on the current Time
    void CalculateScore( int CurrentTime);

    // Tries to add an Action to the current group, true=successful false=failure
    bool AddAction( iAction* action);

    // Let the event control the TrafficLights, returns the time required for the next state-change
    int ExecuteActionGreen  ( cArbitrator *arbi, cNetworkView *view);
    int ExecuteActionOrange ( cArbitrator *arbi, cNetworkView *view);
    /* Returns whether all participants are gone (true) or not (false) */
    bool ExecuteActionRed   ( cArbitrator *arbi, cNetworkView *view, int time);
};

#endif // CLASS_ACTIONGROUP_H
