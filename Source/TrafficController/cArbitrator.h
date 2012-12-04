#ifndef CLASS_ARBITRATOR_H
#define CLASS_ARBITRATOR_H

#include <vector>

#include "EventQueue/iEvent.h"

class cNetworkView;

// Defines the order of how the Arbitrator should behave
namespace ARBIT
{
    enum EVENTORDER
    {
        GREEN = 0,
        ORANGE,
        RED,
    };

    const enum EVENTORDER EventStart = ARBIT::GREEN;
    const enum EVENTORDER EventEnd   = ARBIT::RED;
}

/*
 *
 */
class cArbitrator
{
private:
    std::vector<iEvent> _Queue;

    iEvent* _CurrentEvent;
    ARBIT::EVENTORDER _CurrentState;

public:
    //
    cArbitrator() : _CurrentEvent( NULL), _CurrentState( ARBIT::GREEN) {}
    ~cArbitrator() {}

    void Update( const cNetworkView *);

};

#endif // CLASS_ARBITRATOR_H
