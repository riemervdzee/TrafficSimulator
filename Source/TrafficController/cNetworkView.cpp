#include "cNetworkView.h"
#include "cTrafficController.h"
using namespace std;
using namespace RuneSocket;

// Size of buffers used in the network class
const int bufferSize = 4096;

/*
 * Constructor
 */
cNetworkView::cNetworkView()
{
    // init
    ServerSocket.Listen(1337);
    ServerSocket.SetBlocking( false);
    sockSet.AddSocket( ServerSocket);

    // Output something nice
    cout << "Server started!" << std::endl;
}

/*
 * Deconstructor
 */
cNetworkView::~cNetworkView()
{
    if(!ServerSocket.IsListening())
    {
        ServerSocket.Close();
    }
}

/*
 * Send stuff
 */
void cNetworkView::Send(std::string TrafficLightMessage)
{
    if(ClientSocket.IsConnected())
    {
        msgQueue.push(TrafficLightMessage);
    }
}

/*
 * receive stuff
 */
void cNetworkView::Update()
{
    char buffer[bufferSize];
    buffer[0] = '\0';

    try
    {
        // Poll for socket activity
        if(sockSet.Poll(10))
        {
            try
            {
                // check if the listening socket has activity
                if(sockSet.HasActivity(ServerSocket, READ))
                {
                    ClientSocket = ServerSocket.Accept();

                    ClientSocket.SetBlocking(false);
                    sockSet.AddSocket(ClientSocket);

                    // show message
                    std::cout << "Client connected: " <<
                            GetIPString(ClientSocket.GetRemoteAddress()) << endl;

                    // Notify the TrafficController of the change of network activity
                    if(_TrafficController != NULL)
                    {
                        _TrafficController->SetNetworkState( true);
                    }
                }

                if(sockSet.HasActivity(ClientSocket, READ))
                {
                    int br = ClientSocket.Receive(buffer, bufferSize);
                    std::string buff;
                    int start = 0;

                    if(br > (bufferSize - 1))
                    {
                        std::cout << "Too many bytes to process!" << std::endl;
                    }

                    while(br > 0)
                    {
                        buff = buffer + start; // puts the chars in to the string until '\0'

                        if(_TrafficController != 0)
                        {
                            _TrafficController->TranslateMessage(buff);
                        }

                        br -= (buff.size() + 1);
                        start += (buff.size() + 1);
                    }

                    buffer[0] = '\0';
                }

                if(sockSet.HasActivity(ClientSocket, WRITE))
                {
                    // get messages from the queue and send to client
                    while(!msgQueue.empty())
                    {
                        std::string& msg = msgQueue.front();
                        ClientSocket.Send(msg.c_str(), msg.size() + 1);
                        msgQueue.pop();
                        
                        //std::cout << "Msg send" << std::endl;
                    }
                }

            }
            catch(Exception& e)
            {
                if(e.ErrorCode() != EOperationWouldBlock)
                {
                    if(ClientSocket.IsConnected())
                    {
                        sockSet.RemoveSocket(ClientSocket);
                        ClientSocket.Close();
                        cout << "Client: " << GetIPString(ClientSocket.GetRemoteAddress())
                                << " disconnected!" << std::endl;

                        // Notify the TrafficController of the change of network activity
                        if(_TrafficController != NULL)
                        {
                            _TrafficController->SetNetworkState( false);
                        }
                    }
                    else
                    {
                        std::cout <<"[FATAL ERROR] " << e.PrintError() << endl;

                        // must terminate server
                    }

                    if(!ServerSocket.IsListening())
                    {
                        ServerSocket.Close();
                        sockSet.RemoveSocket(ServerSocket);
                        std::cout << "[FATAL ERROR] HOLY SHIT! " << __FILE__ << " " << __LINE__ << std::endl;

                        // must terminate server
                    }

                }
            }
        } // socket polling
    }
    catch(Exception& e)
    {
        std::cout << "[FATAL ERROR] " << e.PrintError() << endl;

        // must terminate server
    }
}
