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
    catch(RuneSocket::Exception& e)
    {
        std::cout << e.PrintError() << std::endl;
    }
}

void CNetworkView::Translate(const char* buffer, int br)
{
    std::cout << "Bytes received: " << br << std::endl;
    std::string buff;
    int start = 0;
    
    // DEBUG, show messages
    while(br > 0)
    {
        buff = buffer + start; // puts the chars in to the string until '\0'
        std::cout << buff << std::endl;
        br -= (buff.size() + 1);
        start += (buff.size() + 1);
    
        if(buff.compare("exit") == 0)
        {
            std::cout << "Disconnected from the server!" << std::endl;
            socketSet.RemoveSocket(dSocket);
            dSocket.Close();
        }
    }
}

void CNetworkView::UpdateNetwork()
{
    if(dSocket.IsConnected())
    {
        try
        {
            // check for for socket action
            if(socketSet.Poll(16))
            {
                // if this socket really has activity do stuff
                if(socketSet.HasActivity(dSocket, RuneSocket::READ))
                {
                    // receive data
                    int br = dSocket.Receive(recBuffer, bufferSize);
                    
                    // handle data
                    Translate(recBuffer, br);
                    recBuffer[0] = '\0';
                }
            }
            
        }
        catch(RuneSocket::Exception& e)
        {
            if(e.ErrorCode() != RuneSocket::EOperationWouldBlock)
            {
                std::cout << e.PrintError() << " " << e.ErrorCode() << std::endl;
                std::cout << "Disconnected from the server!" << std::endl;
                socketSet.RemoveSocket(dSocket);
                dSocket.Close();
            }
        } 
    }
}
