#include "CSimulationController.h"
#include "CSimulationModel.h"
#include "CSimulationView.h"
#include "CNetworkView.h"

#include <iostream>
#include <fstream>

void CSimulationController::SetNetworkView(CNetworkView *view)
{
    if(view != 0)
    {
        view->SetController(this);
        view->SetModel(mModel);
    }

    if(mModel != 0)
        mModel->RegisterNetworkView(view);
}

void CSimulationController::SetSimulationView(CSimulationView *view)
{
    if(view != 0)
    {
        view->SetController(this);
        view->SetModel(mModel);
    }

    if(mModel != 0)
        mModel->RegisterSimulationView(view);
}
