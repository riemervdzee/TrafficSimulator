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

}


bool cTrafficController::RunStatus()
{
    return !(_SimulationModel->getQuitPress());
}
