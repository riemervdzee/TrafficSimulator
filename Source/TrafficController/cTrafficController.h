#ifndef CLASS_TRAFFICCONTROLLER_H
#define CLASS_TRAFFICCONTROLLER_H

#include <string>
class cSimulationModel;

/*
 * Main controller class of the TrafficControl server
 */
class cTrafficController
{
public:
    // Constructor
    cTrafficController( cSimulationModel *SimulationModel) : _SimulationModel(SimulationModel) {}

    // Functions executed at the beginning and end of the Application
    bool Create();
    void Destroy();

    // Updates the Server
    void Update();

    // Asks whether we should run or not
    bool RunStatus();

    // Let the main controller know any updates of network changes
    void SetNetworkState( bool state);

    // Pass around func for receiving messages (man, I wished we had globals!)
    void TranslateMessage(const std::string& msg);

private:
    // Protected ref to the simulation model NOTICE: CURRENT OBJECT IS _NOT_ THE OWNER OF THIS OBJECT
    cSimulationModel   *_SimulationModel;
};

#endif // CLASS_TRAFFICCONTROLLER_H
