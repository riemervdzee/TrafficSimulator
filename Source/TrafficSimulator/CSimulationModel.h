#ifndef CSIMULATIONMODEL_H
#define CSIMULATIONMODEL_H

#include "../../Source/TrafficSimulator/Timer.h"

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

    // simulation updating
    void UpdateSim();
    bool LoadInputFromFile(const char* fileName);

private:
    void NotifyNetwork(){};
    void NotifySimulation(){};

private:
    CNetworkView    *mNetworkView;
    CSimulationView *mSimulationView;
    CTimer mTimer;
};

#endif // CSIMULATIONMODEL_H
