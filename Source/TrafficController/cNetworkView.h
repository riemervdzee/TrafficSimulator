#ifndef CLASS_NETWORKVIEW_H
#define CLASS_NETWORKVIEW_H

#include <RuneSocket.h>

#include "iAbstractView.h"
#include "iNetworkObserver.h"

/*
 *
 */
class cNetworkView : public iAbstractView, public iNetworkObserver
{
public:
    // Constructor and deconstructor
    cNetworkView();
    ~cNetworkView();

    // Send messages
    void Send( int TrafficLightMessage);

    // Check for any messages
    void Update();

protected:
    RuneSocket::RuneSocketSet    sockSet;
    RuneSocket::RuneListenSocket ServerSocket;
    RuneSocket::RuneDataSocket   ClientSocket;


};

#endif // CLASS_NETWORKVIEW_H
