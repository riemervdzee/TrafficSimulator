#ifndef CSIMULATIONCONTROLLER_H
#define CSIMULATIONCONTROLLER_H

#include "../../Source/TrafficSimulator/CAbstractView.h"

class CSimulationModel;
class CSimulationView;

class CSimulationController
{
public:
    CSimulationController(CSimulationModel* model)
    : mModel( model ), mAppIsRunning(false) {}

    void SetNetworkView(CAbstractView *view);
    void SetSimulationView(CSimulationView *view);

    void LoadInputFile(const char* fileName);

    // mutators
    void SetRunning(bool state) { mAppIsRunning = state;}
    bool GetIsRunning(){ return mAppIsRunning; }
private:
    CSimulationModel    *mModel;
    bool                mAppIsRunning;
};

#endif // CSIMULATIONCONTROLLER_H
