#include "CNetworkView.h"

CNetworkView::CNetworkView()
{
    //ctor
}

CNetworkView::~CNetworkView()
{
    //dtor
}

void CNetworkView::Connect(std::string ip, short port)
{
    try
    {
        // try to connect
        dSocket.Connect( RuneSocket::GetIPAddress(ip), port);
        
        // add to the socket set
        socketSet.AddSocket(dSocket);
    }
    catch(RuneSocket::Exception& E)
    {
        std::cout << "Could not connect to the server!" << std::endl;
    }
}

void CNetworkView::UpdateNetwork()
{
    if(dSocket.IsConnected())
    {
        try
        {
            
        }
        catch(RuneSocket::Exception& E)
        {
            socketSet.RemoveSocket(dSocket);
            dSocket.Close();
        } 
    }
}
