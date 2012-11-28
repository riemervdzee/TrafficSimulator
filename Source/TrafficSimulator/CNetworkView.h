#ifndef CNETWORKVIEW_H
#define CNETWORKVIEW_H

#include "CAbstractView.h"
#include "Network/RuneSocket.h"

const int bufferSize = 8192;

class CNetworkView : public CAbstractView
{
    public:
        ~CNetworkView();
        
        // connect to the specified server
        void Connect(std::string ip, short port);

         // Send pending messages
         // process incoming message for trafficlights
         void UpdateNetwork();
         
    private:
        void Translate(const char* buffer, int bs);
    
    private:
        RuneSocket::RuneSocketSet socketSet;
        RuneSocket::RuneDataSocket dSocket;
        char recBuffer[bufferSize];
             
};

#endif // CNETWORKVIEW_H
