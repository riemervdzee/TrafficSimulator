// class cSimulationModel

#include "cSimulationModel.h"
#include "iNetworkObserver.h"
#include <sstream>

void cSimulationModel::Update()
{
    // update logic
}

void cSimulationModel::UpdateNetwork()
{
    if(_NetworkView != 0)
    {
        _NetworkView->Update();
    }
}

void cSimulationModel::ProcessMessage(const Json::Value& data)
{ 
    // check which message we have
    if(data.isMember("starttime"))
    {
        std::stringstream sStream;
        int hours = 0;
        int minutes = 0;
        
        // init package
        std::cout << "Starttime package" << std::endl;
        
        // parse time
        std::string time = data["starttime"].asString();
        sStream << time.substr(0, 2);
        sStream >> hours;
        sStream.clear();
        sStream << time.substr(3, 2);
        sStream >> minutes;
        
        // convert to seconds
        int timeSeconds = hours * 3600 + minutes * 60;
        
        // DEBUG
        std::cout << "H: " << hours * 3600 << "  M: " << minutes * 60 << std::endl;
        
        // get the multiplier
        _Multiplier = data["multiplier"].asInt();
    }
    else if(data.isMember("light"))
    {
        // loop message
        std::cout << "Loop package" << std::endl;
        
        // do logic
    }
}
