// class cTrafficController

#include "cTrafficController.h"
#include "cSimulationModel.h"

bool cTrafficController::Create()
{


    return true;
}

void cTrafficController::Destroy()
{

}

void cTrafficController::Update()
{
    if(_SimulationModel != 0)
    {
        _SimulationModel->UpdateNetwork();
        _SimulationModel->Update();
    }
}


bool cTrafficController::RunStatus()
{
    return !(_SimulationModel->getQuitPress());
}

void cTrafficController::TranslateMessage(const std::string& msg)
{
    if(_SimulationModel != 0)
    {
        _SimulationModel->ProcessMessage(msg);
    }
}
