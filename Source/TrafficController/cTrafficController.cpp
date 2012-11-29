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
        // parse data and send to model
        Json::Value root;   // will contains the root value after parsing.
        Json::Reader reader;
        bool parsingSuccessful = reader.parse( msg, root );
        if ( !parsingSuccessful )
        {
            // report to the user the failure and their locations in the document.
            std::cout  << "Failed to parse configuration\n"
                       << reader.getFormattedErrorMessages();
        }
        else
        {
            _SimulationModel->ProcessMessage(root);
        }
    }
}
