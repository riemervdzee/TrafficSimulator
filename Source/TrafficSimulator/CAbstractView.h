#ifndef CABSTRACTVIEW_H
#define CABSTRACTVIEW_H

#include "../../Source/TrafficSimulator/ITrafficObserver.h"
#include "../../Source/TrafficSimulator/CSimulationController.h"
#include "../../Source/TrafficSimulator/CSimulationModel.h"

// abstract view class
class CAbstractView : public ITrafficObserver
{
public:
    CAbstractView()
    {
        mController = mModel = 0;
    }

    void SetController(CSimulationController* contr) { mController = contr; }
    void SetModel(CSimulationModel* model) { mModel = model; }

    virtual ~CAbstractView();
    virtual void UpdatePull() = 0;

protected:
    CSimulationController   *mController;
    CSimulationModel        *mModel;
};

#endif // CABSTRACTVIEW_H
