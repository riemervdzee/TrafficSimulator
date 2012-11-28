#ifndef CLASS_SIMULATIONMODEL_H
#define CLASS_SIMULATIONMODEL_H

// Includes
#include <string>

#include "iConsoleObserver.h"
//#include "iNetworkObserver.h"

// Class prototypes
//class iConsoleObserver;
class iNetworkObserver;

/*
 * The model holder of the TrafficServer and AI executor
 */
class cSimulationModel
{
private:
    //bool _IsClientConnected;
    int  _Multiplier;

    // NOTICE: CURRENT OBJECT IS _NOT_ OWNER OF THESE TWO OBJECTS!
    iNetworkObserver *_NetworkView;
    iConsoleObserver *_ConsoleView;

public:
    cSimulationModel() : _Multiplier(1), _NetworkView(NULL), _ConsoleView(NULL) { }

    //bool Create(); // required?

    // Update functions
    void Update();
    void UpdateNetwork();

    // Registers
    inline void RegisterNetworkView( iNetworkObserver *Observer) { _NetworkView = Observer;}
    inline void RegisterConsoleView( iConsoleObserver *Observer) { _ConsoleView = Observer;}

    // Check if we got a quit press or not
    inline bool getQuitPress() { return _ConsoleView->GetQuitPress(); }

    // Sends a message to the console
    inline void NotifyConsole( std::string Message) { _ConsoleView->Print( Message);}



    /*TrafficLaneGroup[4] _CrossRoad; */ // Beter uitwerken!
};

#endif // CLASS_SIMULATIONMODEL_H
