#ifndef CSIMULATIONCONTROLLER_H
#define CSIMULATIONCONTROLLER_H

#include "../../Source/TrafficSimulator/CSimulationModel.h"
#include "../../Source/TrafficSimulator/CAbstractView.h"

class CSimulationController
{
public:
    CSimulationController(CSimulationModel &model)
    : mModel( &model ) {}

    void SetNetworkView(CAbstractView *view);
    void SetSimulationView(CAbstractView *view);

private:
    CSimulationModel    *mModel;
};

#endif // CSIMULATIONCONTROLLER_H
