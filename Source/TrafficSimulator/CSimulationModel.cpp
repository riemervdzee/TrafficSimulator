#include "CSimulationModel.h"
#include "CSimulationView.h"
#include "CNetworkView.h"
#include "TDW/TDWDefs.h"

CSimulationModel::CSimulationModel()
{
    mNetworkView = 0;
    mSimulationView = 0;
    mTimer.Create();

    laneGroup[DIRECTION.NORTH].SetDirectionType( DIRECTION.NORTH);
    laneGroup[DIRECTION.SOUTH].SetDirectionType( DIRECTION.SOUTH);
    laneGroup[DIRECTION.EAST].SetDirectionType( DIRECTION.EAST);
    laneGroup[DIRECTION.WEST].SetDirectionType( DIRECTION.WEST);
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
        LoadEntities(mSimulationView->GetEntities());
    }
}

void CSimulationModel::LoadEntities(std::vector<TDWEntity>& ents)
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
