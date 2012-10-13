#ifndef ITRAFFICSUBJECT_H
#define ITRAFFICSUBJECT_H

#include "../../Source/TrafficSimulator/ITrafficObserver.h"

// Interface for simulation subjects
class ITrafficSubject
{
public:
    virtual void RegisterNetworkView(ITrafficObserver* observer) = 0;
    virtual void RegisterSimulationView(ITrafficObserver* observer) = 0;
    virtual void NotifyNetwork() = 0;
    virtual void NotifySimulation() = 0;
};

#endif // ITRAFFICSUBJECT_H
