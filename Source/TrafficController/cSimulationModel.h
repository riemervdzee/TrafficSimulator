#ifndef CLASS_SIMULATIONMODEL_H
#define CLASS_SIMULATIONMODEL_H

// Includes
#include <string>

// Class prototypes
class iConsoleObserver;
class iNetworkObserver;

/*
 * The model holder of the TrafficServer and AI executor
 */
class cSimulationModel
{
public:
    cSimulationModel() : _IsClientConnected(false), _Multiplier(1), _NetworkView(NULL), _ConsoleView(NULL) {}

    //bool Create(); // required?

    void Update();

    // Registers
    void RegisterConsoleView( iConsoleObserver *Observer);
    void RegisterNetworkView( iNetworkObserver *Observer);
    void NotifyConsole( std::string Message);
    void UpdateNetwork();

private:
    bool _IsClientConnected;
    int  _Multiplier;

    // NOTICE: CURRENT OBJECT IS _NOT_ OWNER OF THESE TWO OBJECTS!
    iNetworkObserver *_NetworkView;
    iConsoleObserver *_ConsoleView;

    /*TrafficLaneGroup[4] _CrossRoad; */ // Beter uitwerken!
};

#endif // CLASS_SIMULATIONMODEL_H
