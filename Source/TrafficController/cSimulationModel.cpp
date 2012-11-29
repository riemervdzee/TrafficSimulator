// class cSimulationModel

#include "cSimulationModel.h"
#include "iNetworkObserver.h"

void cSimulationModel::Update()
{

}

void cSimulationModel::UpdateNetwork()
{
    if(_NetworkView != 0)
    {
        _NetworkView->Update();
    }
}

void cSimulationModel::ProcessMessage(const std::string& msg)
{
    NotifyConsole(msg);
}
