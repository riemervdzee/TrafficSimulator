#ifndef CSIMULATIONMODEL_H
#define CSIMULATIONMODEL_H

#include <queue>
#include <json/json-forwards.h>
#include <json/json.h>

#include "Timer.h"
#include "CTrafficLaneGroup.h"
#include "CParticipant.h"
#include "CTrafficLight.h"
#include "TrafficDefs.h"
#include "TDW/TDWdefs.h"

class CNetworkView;
class CSimulationView;
class SimulationQueueParticipant_t;

class CSimulationModel
{
public:
    CSimulationModel();
    ~CSimulationModel();

    // inhereted
    void RegisterNetworkView(CNetworkView* observer);
    void RegisterSimulationView(CSimulationView* observer);

    // simulation updating
    void UpdateSim();

    // load entities (waypoints & trafficlights) from the simulation view
    void LoadInputFromFile(const char* fileName);
    void LoadEntities();

    // getters for view
    std::vector<CTrafficLight>& GetTrafficLigths() { return trafficLights; }
    std::vector<CParticipant>& GetParticipants() { return participants; }

private:
    void NotifyNetwork(){};
    void NotifySimulation(){};

    // Simulation updating
    void UpdateParticipants(float dt);

    // INPUT FILE PROCESSING
    void LoadParticipants(Json::Value& root);
    void ParseToLocation(const std::string& str, SimulationQueueParticipant_t& dest);
    void ParseFromLocation(const std::string& str, SimulationQueueParticipant_t& dest);
    TRADEFS::DIRECTION GetDirection(const char val);
    int GetLane(char val);
    // END INPUT FILE PROCESSING

private:
    CNetworkView    *mNetworkView;
    CSimulationView *mSimulationView;

    // timer stuff
    float simTime;
    CTimer mTimer;

    CTrafficLaneGroup                                   laneGroups[4];
    std::priority_queue<SimulationQueueParticipant_t>   queue;
    std::vector<CTrafficLight>                          trafficLights;
    std::vector<CParticipant>                           participants;
};

// data structure for the queue
struct SimulationQueueParticipant_t
{
    int time;
    TRADEFS::PARTICIPANTS type;
    TRADEFS::DIRECTION fromDirection;
    TRADEFS::DIRECTION toDirection;
    int fromLane;
    int toLane;

    bool operator < ( const SimulationQueueParticipant_t &a ) const {
        return  a.time < time;
    }
};

#endif // CSIMULATIONMODEL_H
