#include "CNetworkView.h"
#include "CSimulationModel.h"

#include <json/json-forwards.h>
#include <json/json.h>

CNetworkView::~CNetworkView()
{
    if(dSocket.IsConnected())
    {
        socketSet.RemoveSocket(dSocket);
        dSocket.Close();
    }
}

bool CNetworkView::Connect(std::string ip, short port)
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
        
        return true;
    }
    catch(RuneSocket::Exception& e)
    {
        std::cout << e.PrintError() << std::endl;
        return false;
    }
}

void CNetworkView::Translate(const char* buffer, int br)
{
    std::cout << "Bytes received: " << br << std::endl;
    int start = 0;

    while(br > 0)
    {
        std::string buff = buffer + start; // puts the chars in to the string until '\0'

        // parse data and send to model
        Json::Value root;   // will contains the root value after parsing.
        Json::Reader reader;
        std::cout << buff << std::endl; // debug
        
        if ( reader.parse( buff, root ) )
        {
            mModel->ProcessMsg(root);
        }
        else
        {
            std::cout << "ERORRR" << std::endl;
            // report to the user the failure and their locations in the document.
            std::cout  << "Failed to parse configuration\n"
                       << reader.getFormattedErrorMessages();
            break;
        }
        
                
        br -= (buff.size() + 1);
        start += (buff.size() + 1);
    }
}

// Send a string
void CNetworkView::SendString(const std::string& data)
{
    if(dSocket.IsConnected())
    {
        sendQueue.push(data);
    }
    else
    {
        std::cout << "Not connected to a server! can send!" << std::endl;
    }
}

void CNetworkView::UpdateNetwork()
{
    if(dSocket.IsConnected())
    {
        try
        {
            // check for for socket action, 30 fps
            if(socketSet.Poll(32))
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
                
                // send data if possible
                if(socketSet.HasActivity(dSocket, RuneSocket::WRITE))
                {
                    int sendCount = 0;
                    while(!sendQueue.empty() && !(sendCount > maxSend) )
                    {
                        std::string& data = sendQueue.front();
                        
                        // send the data, + 1 is for '\0' as it is a c-string
                        dSocket.Send( data.c_str(), data.size() + 1 );
                        
                        // get rid of the message
                        sendQueue.pop();
                        sendCount++;
                    }
                }
            }
            
        }
        catch(RuneSocket::Exception& e)
        {
            if(e.ErrorCode() != RuneSocket::EOperationWouldBlock)
            {
                //std::cout << e.PrintError() << std::endl;
                std::cout << "Disconnected from the server!" << std::endl;
                socketSet.RemoveSocket(dSocket);
                dSocket.Close();
                
                // tell the model we disconnected
                if(mModel != 0)
                {
                    mModel->Disconnected();
                }
            }
        } 
    }
}
