#ifndef CLASS_SIMULATIONMODEL_H
#define CLASS_SIMULATIONMODEL_H

// Includes
#include <string>
#include <ctime>

#include "json/json-forwards.h"
#include "json/json.h"
#include "iConsoleObserver.h"
#include "cArbitrator.h"

// Class prototypesx
class iNetworkObserver;

/*
 * The model holder of the TrafficServer and AI executor
 */
class cSimulationModel
{
private:
    // NOTICE: CURRENT OBJECT IS _NOT_ OWNER OF THESE TWO OBJECTS!
    iNetworkObserver *_NetworkView;
    iConsoleObserver *_ConsoleView;

    // Bool tells whether we got a connection
    bool _IsClientConnected;

    // Arbiter obj, handles all events
    cArbitrator _Arbitrator;

    // Time variables (note that we got a distiction between Realtime = humanlife time, and Simtime = time in the application)
    int _CurrentSimTime;
    int _Multiplier;
    time_t _CurrentRealTime;

public:
    // Constructor
    cSimulationModel() :  _NetworkView(NULL), _ConsoleView(NULL),
        _IsClientConnected(false), _CurrentSimTime(0), _Multiplier(0), _CurrentRealTime(0) { }

    // Update functions
    void Update();
    void UpdateNetwork();

    // Registers
    inline void RegisterNetworkView( iNetworkObserver *Observer) { _NetworkView = Observer;}
    inline void RegisterConsoleView( iConsoleObserver *Observer) { _ConsoleView = Observer;}

    // Message handlers when we got a Connection or not
    void EventConnectionEstablished();
    void EventConnectionLost();

    // Check if we got a quit press or not
    inline bool getQuitPress() { if(_ConsoleView != 0) return _ConsoleView->GetQuitPress(); else return false; }

    // Sends a message to the console
    inline void NotifyConsole(const std::string& msg) { if(_ConsoleView != 0) _ConsoleView->Print(msg);}

    void ProcessMessage(const Json::Value& data);
};

#endif // CLASS_SIMULATIONMODEL_H
