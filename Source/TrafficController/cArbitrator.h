#ifndef CLASS_ARBITRATOR_H
#define CLASS_ARBITRATOR_H

#include <vector>

#include "EventQueue/iEvent.h"

class iNetworkObserver;

/* Special defines for cArbitrator */
namespace ARBIT
{
    // Defines the order of how the Arbitrator should behave
    enum EVENTORDER
    {
        GREEN = 0,
        ORANGE,
        RED,
    };

    const enum EVENTORDER EventStart = ARBIT::GREEN;
    const enum EVENTORDER EventEnd   = ARBIT::RED;

    struct LaneControl_t
    {
        iEvent* lane[8];
    };
}

/*
 *
 */
class cArbitrator
{
private:
    std::vector<iEvent*> _Queue;
    ARBIT::LaneControl_t _LaneControls[4];

    iEvent* _CurrentEvent;
    ARBIT::EVENTORDER _CurrentState;

    int _TimeNextEvent;

public:
    //
    cArbitrator(); : _CurrentEvent( NULL), _CurrentState( ARBIT::GREEN)
    ~cArbitrator() {}

    void AddEvent( TRADEFS::SimulationQueueParticipant_t Event);

    void Update( const iNetworkObserver*, int t);

};

#endif // CLASS_ARBITRATOR_H
