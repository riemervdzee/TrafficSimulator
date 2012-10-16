#include "CSimulationModel.h"
#include "CSimulationView.h"
#include "CNetworkView.h"

CSimulationModel::CSimulationModel()
{
    mNetworkView = 0;
    mSimulationView = 0;
}

CSimulationModel::~CSimulationModel()
{
    if(mNetworkView)
        delete mNetworkView;

    if(mSimulationView)
        delete mNetworkView;
}

void CSimulationModel::RegisterNetworkView(CNetworkView* observer)
{
    if(observer != 0)
        mNetworkView = observer;
}

void CSimulationModel::RegisterSimulationView(CSimulationView* observer)
{
    if(observer != 0)
        mSimulationView = observer;
}

void CSimulationModel::UpdateSim()
{
    // update views and simulation
    mSimulationView->Update(1.0f);
    mNetworkView->UpdateNetwork();

    // draw
    mSimulationView->Draw();
}
