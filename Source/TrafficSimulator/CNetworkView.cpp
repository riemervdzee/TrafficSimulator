#include "CNetworkView.h"

CNetworkView::~CNetworkView()
{
    if(dSocket.IsConnected())
    {
        socketSet.RemoveSocket(dSocket);
        dSocket.Close();
    }
}

void CNetworkView::Connect(std::string ip, short port)
{
    try
    {
        // try to connect
        dSocket.Connect( RuneSocket::GetIPAddress(ip), port);
        
        // message
        std::cout << "Connected to: " << RuneSocket::GetIPString(dSocket.GetRemoteAddress())
                << std::endl;
        
        // add to the socket set
        socketSet.AddSocket(dSocket);
    }
    catch(RuneSocket::Exception& E)
    {
        std::cout << "Could not connect to the server!" << std::endl;
    }
}

void CNetworkView::Translate(const char* buffer)
{
    std::string buff(buffer); // puts the chars in to the string until '\0'
    
    // DEBUG, show message
    std::cout << buff << std::endl;
}

void CNetworkView::UpdateNetwork()
{
    if(dSocket.IsConnected())
    {
        try
        {
            // wait for 16 min for socket action
            if(socketSet.Poll(16))
            {
                // if this socket really has activity do stuff
                if(socketSet.HasActivity(dSocket))
                {
                    // receive data
                    dSocket.Receive(recBuffer, bufferSize);
                    
                    // handle data
                    Translate(recBuffer);
                }
            }
            
        }
        catch(RuneSocket::Exception& e)
        {
            if(e.ErrorCode() != RuneSocket::EOperationWouldBlock)
            {
                std::cout << e.PrintError() << std::endl;
                socketSet.RemoveSocket(dSocket);
                dSocket.Close();
            }
        } 
    }
}
