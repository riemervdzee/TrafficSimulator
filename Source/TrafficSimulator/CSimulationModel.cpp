#include "CSimulationModel.h"
#include "CSimulationView.h"
#include "CNetworkView.h"
#include "TDW/TDWDefs.h"

CSimulationModel::CSimulationModel()
{
    mNetworkView = 0;
    mSimulationView = 0;
    mTimer.Create();

    // init lanes
    laneGroups[0].SetDirectionType(0); // NORTH
    laneGroups[1].SetDirectionType(1); // SOUTH
    laneGroups[2].SetDirectionType(2); // EAST
    laneGroups[3].SetDirectionType(3); // WEST
}

CSimulationModel::~CSimulationModel()
{
    if(mNetworkView)
    {
        delete mNetworkView;
        mNetworkView = 0;
    }

    if(mSimulationView)
    {
         mSimulationView->Dispose();
         delete mSimulationView;
         mSimulationView = 0;
    }
}

void CSimulationModel::RegisterNetworkView(CNetworkView* observer)
{
    if(observer != 0)
        mNetworkView = observer;
}

void CSimulationModel::RegisterSimulationView(CSimulationView* observer)
{
    if(observer != 0)
    {
        mSimulationView = observer;
        mSimulationView->Init();

        // load entities
        LoadEntities();
    }
}

void CSimulationModel::LoadEntities()
{
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
