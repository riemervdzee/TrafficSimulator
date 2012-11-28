#ifndef CNETWORKVIEW_H
#define CNETWORKVIEW_H

#include "CAbstractView.h"
#include "Network/RuneSocket.h"
#include <queue>

const int bufferSize = 8192;
const int maxSend = 16;

class CNetworkView : public CAbstractView
{
    public:
        ~CNetworkView();
        
        // connect to the specified server
        bool Connect(std::string ip, short port);

        // Send pending messages
        // process incoming message for trafficlights
        void UpdateNetwork();
        
        // Send a string
        void SendString(const std::string& data);
         
    private:
        void Translate(const char* buffer, int bs);
    
    private:
        RuneSocket::RuneSocketSet socketSet;
        RuneSocket::RuneDataSocket dSocket;
        char recBuffer[bufferSize];
        std::queue<std::string> sendQueue;
};

#endif // CNETWORKVIEW_H
