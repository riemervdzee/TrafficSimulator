#ifndef CNETWORKVIEW_H
#define CNETWORKVIEW_H

#include "CAbstractView.h"
#include "RuneSocket.h"

class CNetworkView : public CAbstractView
{
    public:
        CNetworkView();
        ~CNetworkView();
        
        // connect to the specified server
        void Connect(std::string ip, short port);

         // Send pending messages
         // process incoming message for trafficlights
         void UpdateNetwork();
    private:
        RuneSocket::RuneSocketSet socketSet;
        RuneSocket::RuneDataSocket dSocket;
             
};

#endif // CNETWORKVIEW_H
