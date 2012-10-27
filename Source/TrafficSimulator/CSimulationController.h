#ifndef CSIMULATIONCONTROLLER_H
#define CSIMULATIONCONTROLLER_H

class CSimulationModel;
class CSimulationView;
class CNetworkView;

class CSimulationController
{
public:
    CSimulationController(CSimulationModel* model)
    : mModel( model ), mAppIsRunning(false) {}
    ~CSimulationController()
    {
        mModel = 0;
    }

    void SetNetworkView(CNetworkView *view);
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
