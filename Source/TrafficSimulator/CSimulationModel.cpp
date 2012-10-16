#include "CSimulationModel.h"
#include "CSimulationView.h"
#include "CNetworkView.h"

CSimulationModel::CSimulationModel()
{
    mNetworkView = 0;
    mSimulationView = 0;
    mTimer.Create();
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
    mTimer.Tick();

    // update views and simulation
    mSimulationView->Update( mTimer.GetDeltaTime() );
    mNetworkView->UpdateNetwork();

    // draw
    mSimulationView->Draw();
}
