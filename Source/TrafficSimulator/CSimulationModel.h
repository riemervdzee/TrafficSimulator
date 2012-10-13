#ifndef CSIMULATIONMODEL_H
#define CSIMULATIONMODEL_H

#include "../../Source/TrafficSimulator/ITrafficSubject.h"

class CSimulationModel : public ITrafficSubject
{
public:
    CSimulationModel();

    // inhereted
    void RegisterNetworkView(ITrafficObserver* observer){};
    void RegisterSimulationView(ITrafficObserver* observer){};

    // simulation updating
    void UpdateSim();
    bool LoadInputFromFile(const char* fileName);

private:
    void NotifyNetwork(){};
    void NotifySimulation(){};

private:
    ITrafficObserver   *mNetworkView;
    ITrafficObserver   *mSimulationView;
};

#endif // CSIMULATIONMODEL_H
