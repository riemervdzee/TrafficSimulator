#ifndef CSIMULATIONMODEL_H
#define CSIMULATIONMODEL_H

#include <queue>
#include <list>
#include <json/json-forwards.h>
#include <json/json.h>

#include "Timer.h"
#include "CTrafficLaneGroup.h"
#include "CTrafficLane.h"
#include "CParticipant.h"
#include "CTrafficLight.h"
#include "TrafficDefs.h"
#include "TDW/TDWDefs.h"

class CNetworkView;
class CSimulationView;

class CSimulationModel
{
public:
    CSimulationModel();
    ~CSimulationModel();

    // inhereted
    void RegisterNetworkView(CNetworkView* observer);
    void RegisterSimulationView(CSimulationView* observer);
    CNetworkView* GetNetworkView() { return mNetworkView; }
    
    // state
    void Connected();
    void Disconnected();
    void ProcessMsg(const Json::Value& array);

    // simulation updating
    void UpdateSim();

    // load entities (waypoints & trafficlights) from the simulation view
    void LoadInputFromFile(const char* fileName);
    void LoadEntities();

    // getters for view
    std::vector<CTrafficLight>& GetTrafficLigths() { return trafficLights; }
    std::list<CParticipant>& GetParticipants() { return participants; }

private:
    // Simulation updating
    void UpdateParticipants(float dt);

    // INPUT FILE PROCESSING
    void LoadParticipants(Json::Value& root);
    void ParseToLocation(const std::string& str, TRADEFS::SimulationQueueParticipant_t& dest);
    void ParseFromLocation(const std::string& str, TRADEFS::SimulationQueueParticipant_t& dest);
    void ParseLocation(const std::string& str, int& dir, int& lane);
    void ParseLightState(const std::string& str, int& state);
    TRADEFS::DIRECTION GetDirection(const char val);
    int GetLane(char val);
    // END INPUT FILE PROCESSING

private:
    CNetworkView    *mNetworkView;
    CSimulationView *mSimulationView;

    // timer stuff
    float simTime;
    CTimer mTimer;
    int speedMultiplier;
    bool mSimStarted;

    CTrafficLaneGroup                                           laneGroups[4];
    std::priority_queue<TRADEFS::SimulationQueueParticipant_t>  queue;
    std::vector<CTrafficLight>                                  trafficLights;
    std::list<CParticipant>                                     participants;
};

#endif // CSIMULATIONMODEL_H
