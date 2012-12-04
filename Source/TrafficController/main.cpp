#include <iostream>

#include "Network/RuneSocket.h"

#include "TrafficDefs.h"
#include "Util.h"

#include "iAbstractView.h"
#include "iConsoleObserver.h"
#include "iNetworkObserver.h"

#include "cConsoleView.h"
#include "cNetworkView.h"
#include "cSimulationModel.h"
#include "cTrafficController.h"
using namespace std;

/*
 * Main entry of the TrafficController program
 */
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
        // Let the controller do his thing
        controller.Update();

        // Sleep 20ms
        TC_Sleep( 20);
    }

    // Destroy objects
    controller.Destroy();

    return 0;
}
