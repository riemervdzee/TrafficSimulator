#ifndef CSIMULATIONMODEL_H
#define CSIMULATIONMODEL_H

class CAbstractView;
class CSimulationView;

class CSimulationModel
{
public:
    CSimulationModel();
    ~CSimulationModel();

    // inhereted
    void RegisterNetworkView(CAbstractView* observer);
    void RegisterSimulationView(CSimulationView* observer);

    // simulation updating
    void UpdateSim();
    bool LoadInputFromFile(const char* fileName);

private:
    void NotifyNetwork(){};
    void NotifySimulation(){};

private:
    CAbstractView   *mNetworkView;
    CSimulationView   *mSimulationView;
};

#endif // CSIMULATIONMODEL_H
