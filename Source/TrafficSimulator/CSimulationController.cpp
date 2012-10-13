#include "CSimulationController.h"

void CSimulationController::SetNetworkView(CAbstractView *view)
{
    if(view != 0)
    {
        view->SetController(this);
        view->SetModel(mModel);
    }

    if(mModel != 0)
        mModel->RegisterNetworkView(view);
}

void CSimulationController::SetSimulationView(CAbstractView *view)
{
    if(view != 0)
    {
        view->SetController(this);
        view->SetModel(mModel);
    }

    if(mModel != 0)
        mModel->RegisterSimulationView(view);
}
