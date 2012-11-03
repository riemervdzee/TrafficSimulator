#ifndef CSIMULATIONMODEL_H
#define CSIMULATIONMODEL_H

#include <queue>

#include "Timer.h"
#include "CTrafficLaneGroup.h"
#include "TrafficDefs.h"
#include "TDW/TDWdefs.h"

#include <json/json-forwards.h>
#include <json/json.h>

class CNetworkView;
class CSimulationView;
class CSimulationQueueParticipant;

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
    void LoadInputFromFile(const char* fileName);

    void LoadEntities();

private:
    void NotifyNetwork(){};
    void NotifySimulation(){};

    void LoadParticipants(Json::Value& root);
    void ParseToLocation(const std::string& str, CSimulationQueueParticipant& dest);
    void ParseFromLocation(const std::string& str, CSimulationQueueParticipant& dest);
    TRADEFS::DIRECTION GetDirection(const char val);
    int GetLane(char val);

private:
    CNetworkView    *mNetworkView;
    CSimulationView *mSimulationView;
    CTimer mTimer;

    CTrafficLaneGroup   laneGroups[4];
    std::priority_queue<CSimulationQueueParticipant> queue;

    // Vector for the actual participants TODO visibility?
    //std::vector<
};


class CSimulationQueueParticipant
{
public:
    int time;
    TRADEFS::PARTICIPANTS type;
    TRADEFS::DIRECTION fromDirection;
    TRADEFS::DIRECTION toDirection;
    int fromLane;
    int toLane;

    bool operator < ( const CSimulationQueueParticipant &a ) const {
        return time < a.time;
    }
};

#endif // CSIMULATIONMODEL_H
