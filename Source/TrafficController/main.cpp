#include <iostream>


#include "Network/RuneSocket.h"

#include "TrafficDefs.h"

#include "iAbstractView.h"
#include "iConsoleObserver.h"
#include "iNetworkObserver.h"

#include "cConsoleView.h"
#include "cNetworkView.h"
#include "cSimulationModel.h"
#include "cTrafficController.h"
using namespace std;

int main()
{
    // Create model and views
    cSimulationModel model;
    cConsoleView viewConsole;
    cNetworkView viewNetwork;

    model.RegisterConsoleView( &viewConsole);
    model.RegisterNetworkView( &viewNetwork);

    // Create controller
    cTrafficController controller( &model);
    viewNetwork.SetController(&controller);
    viewConsole.SetController(&controller);
    controller.Create();

    // Main while loop
    while( controller.RunStatus())
    {
        controller.Update();

        // sleep 1 ms, convert to microseconds
#ifdef WIN32
        Sleep( 1);
#else
        usleep(1 * 1000);
#endif
    }

    // Destroy objects
    controller.Destroy();

    return 0;
}
