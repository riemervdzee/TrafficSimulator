// class cSimulationModel

#include "cSimulationModel.h"
#include "iNetworkObserver.h"
#include <sstream>
using namespace std;

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
    // Check for a starttime package (init pack)
    if(data.isMember("starttime"))
    {
        stringstream sStream;
        int hours = 0;
        int minutes = 0;

        // init package
        cout << "Starttime package" << endl;

        // parse time
        string time = data["starttime"].asString();
        sStream << time.substr(0, 2);
        sStream >> hours;
        sStream.clear();
        sStream << time.substr(3, 2);
        sStream >> minutes;

        // convert to seconds
        int timeSeconds = hours * 3600 + minutes * 60;

        // DEBUG
        cout << "H: " << hours * 3600 << "  M: " << minutes * 60 << endl;

        // get the multiplier
        _Multiplier = data["multiplier"].asInt();
    }
    // The received package is a light loop package
    else if(data.isMember("light"))
    {
        // We find the empty = true packages quite boring
        if ( data["empty"].asBool() == true)
        {
            cout << "We are too fly for empty=true packages" << endl;
            return;
        }


        // loop message
        cout << "Loop package" << endl;

        // do logic
        cout << data["type"].asString() << endl;
        cout << data["light"].asString() << endl;
        cout << data["loop"].asString() << endl;
        cout << data["empty"].asString() << endl;
        cout << data["to"].asString() << endl;
    }
}
