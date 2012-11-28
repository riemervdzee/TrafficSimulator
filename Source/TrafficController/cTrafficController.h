#ifndef CLASS_TRAFFICCONTROLLER_H
#define CLASS_TRAFFICCONTROLLER_H


class cSimulationModel;

/*
 * Main controller class of the TrafficControl server
 */
class cTrafficController
{
public:
    cTrafficController( cSimulationModel *SimulationModel) : _SimulationModel(SimulationModel) {}

    bool Create();
    void Destroy();

    void Update();
    bool RunStatus();

private:
//    CSimulationModel        *mModel;
    cSimulationModel   *_SimulationModel;
};

#endif // CLASS_TRAFFICCONTROLLER_H
