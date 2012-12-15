#ifndef CLASS_NETWORKVIEW_H
#define CLASS_NETWORKVIEW_H

#include "Network/RuneSocket.h"

#include "iAbstractView.h"
#include "iNetworkObserver.h"
#include <queue>

/*
 * Implementer of our network
 */
class cNetworkView : public iAbstractView, public iNetworkObserver
{
public:
    // Constructor and deconstructor
    cNetworkView();
    ~cNetworkView();

    // Send messages
    void Send(std::string TrafficLightMessage);

    // Check for any messages
    void Update();

protected:
    RuneSocket::RuneSocketSet    sockSet;
    RuneSocket::RuneListenSocket ServerSocket;
    RuneSocket::RuneDataSocket   ClientSocket;
    std::queue<std::string> msgQueue;
};

#endif // CLASS_NETWORKVIEW_H
