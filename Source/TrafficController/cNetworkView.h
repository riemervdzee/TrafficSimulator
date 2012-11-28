#ifndef CLASS_NETWORKVIEW_H
#define CLASS_NETWORKVIEW_H


#include "iAbstractView.h"
#include "iNetworkObserver.h"

/*
 *
 */
class cNetworkView : public iAbstractView, public iNetworkObserver
{
public:
    // Empty constructor to override interface (private/non-working) constructors
    cNetworkView() {}

    //
    void Send( int TrafficLightMessage);

    //
    void Update();
};

#endif // CLASS_NETWORKVIEW_H
