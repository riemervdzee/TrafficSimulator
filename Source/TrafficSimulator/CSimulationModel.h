#ifndef CSIMULATIONMODEL_H
#define CSIMULATIONMODEL_H

#include <queue>

#include "Timer.h"
#include "CTrafficLaneGroup.h"
#include "TrafficDefs.h"
#include "TDW/TDWdefs.h"

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
    bool LoadInputFromFile(const char* fileName);

    void LoadEntities();

private:
    void NotifyNetwork(){};
    void NotifySimulation(){};

private:
    CNetworkView    *mNetworkView;
    CSimulationView *mSimulationView;
    CTimer mTimer;

    // model
    CTrafficLaneGroup   laneGroups[4];

    // Queue for participants who are about to join TODO visibility?
    std::priority_queue< CSimulationQueueParticipant> queue;

    // Vector for the actual participants TODO visibility?
    //std::vector<
};


class CSimulationQueueParticipant
{
public:
    int time;
    TDWDEFS::PARTICIPANTS type;
    TDWDEFS::DIRECTION fromDirection;
    TDWDEFS::DIRECTION toDirection;
    int fromLane;
    int toLane;

    bool operator < ( const CSimulationQueueParticipant &a ) const {
        return time < a.time;
    }

};

#endif // CSIMULATIONMODEL_H
