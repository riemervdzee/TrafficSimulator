#ifndef CLASS_SIMULATIONMODEL_H
#define CLASS_SIMULATIONMODEL_H

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
    RegisterConsoleView( iConsoleObserver);
    RegisterNetworkView( iNetworkObserver);
    NotifyConsole( string Message);
    UpdateNetwork();

private:
    bool _IsClientConnected;
    int  _Multiplier;
    iNetworkObserver *_NetworkView;
    iConsoleOBserver *_ConsoleView;
    /*TrafficLaneGroup[4] _CrossRoad; */ // Beter uitwerken!
};

#endif // CLASS_SIMULATIONMODEL_H
