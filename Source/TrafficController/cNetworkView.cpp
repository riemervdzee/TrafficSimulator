// class cNetworkView

#include "cNetworkView.h"
using namespace std;
using namespace RuneSocket;

/*
 * Constructor
 */
cNetworkView::cNetworkView()
{
    // init
    ServerSocket.Listen( 1337);
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
void cNetworkView::Send( int TrafficLightMessage)
{

}

/*
 * receive stuff
 */
void cNetworkView::Update()
{

}
