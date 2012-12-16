#ifndef CLASS_ARBITRATOR_H
#define CLASS_ARBITRATOR_H

#include <vector>

#include "TrafficDefs.h"
#include "EventQueue/cActionGroup.h"

class iNetworkObserver;

/*
 * Special defines for cArbitrator
 */
namespace ARBIT
{
    // Defines the order of how the Arbitrator should behave
    enum EVENTORDER
    {
        GREEN = 0,
        ORANGE,
        RED,
    };

    // Helper struct
    struct LaneControl_t
    {
        iAction* lane[ TRADEFS::MAXLANES];
    };
}

/*
 * Our Arbitrator/referee class
 */
class cArbitrator
{
private:
    // The event queue of actions we are executing
    std::vector<cActionGroup*> _Queue;

    // Caching
    ARBIT::LaneControl_t _LaneControls[ TRADEFS::MAXGROUPS];

    // Current cActionGroup object (may be oudated), depending on NextLightState =green (is outdated), otherwise up-to-date
    cActionGroup* _CurrentEventGroup;

    // The next Event we are processing
    ARBIT::EVENTORDER _NextLightState;

    // The time we wait till the next state is handled
    int _TimeNextEvent;

    // Clears the Cache
    void FlushCache();

public:
    // Constructor/deconstructor
    cArbitrator();
    ~cArbitrator() {}

    // New events where the arbitrator can do stuff when there is a connection or when we lost it
    void EventConnectionEstablished( iNetworkObserver *view);
    void EventConnectionLost();

    // Update function
    void Update( iNetworkObserver*, int t);

    // Adds a loop Event to the Arbitrator
    void AddEvent( TRADEFS::SimulationQueueParticipant_t Event);

    // Clears a specific lane
    void ClearLane( int LaneGroup, int Lane);
};

#endif // CLASS_ARBITRATOR_H
