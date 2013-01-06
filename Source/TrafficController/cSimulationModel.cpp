// class cSimulationModel

#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cSimulationModel.h"
#include "iNetworkObserver.h"
#include "TrafficDefs.h"
using namespace std;

// Prototypes to do the inverse of the PacketMaster helper class
// TODO review if this can be inside the PacketMaster
bool GetEmpty( string e);
int GetLoop( string loop);
TRADEFS::PARTICIPANTS GetType( string type);
TRADEFS::DIRECTION GetDir( string dir);
TRADEFS::TRAFFICLIGHTSTATE GetLightState( string state);

/**/
void cSimulationModel::Update()
{
    // TODO there is no check when we loose the connection with the client
    if( !_IsClientConnected)
        return;

    // Calculate new time values
    time_t newTime = time(NULL);
    int timeDifference = (newTime - _CurrentRealTime) * _Multiplier; // Time difference according to SimTime
    _CurrentSimTime += timeDifference;                               // Add difference to sim time
    _CurrentRealTime = newTime;

    // Update the arbitrator
    _Arbitrator.Update( _NetworkView, _CurrentSimTime);
}

void cSimulationModel::UpdateNetwork()
{
    if(_NetworkView != 0)
    {
        _NetworkView->Update();
    }
}


void cSimulationModel::EventConnectionEstablished()
{
    // Set var
    _IsClientConnected = true;
    _Arbitrator.EventConnectionEstablished( _NetworkView);
}

void cSimulationModel::EventConnectionLost()
{
    // Set var
    _IsClientConnected = false;
    _Arbitrator.EventConnectionLost();
}

void cSimulationModel::ProcessMessage(const Json::Value& array)
{
    stringstream sStream;

    // Go through all packages
    for( unsigned int i = 0; i < array.size(); ++i)
    {
        const Json::Value &data = array[i];

        // check which message we have
        // Check for a starttime package (init pack)
        if(data.isMember("starttime"))
        {
            int hours = 0;
            int minutes = 0;

            // init package
            cout << "Starttime package" << endl;

            // parse time
            string stime = data["starttime"].asString();
            sStream << stime.substr(0, 2);
            sStream >> hours;
            sStream.clear();
            sStream << stime.substr(3, 2);
            sStream >> minutes;

            // convert to seconds
            _CurrentSimTime = hours * 3600 + minutes * 60;

            // DEBUG
            cout << "H: " << hours * 3600 << "  M: " << minutes * 60 << endl;

            // get the multiplier
            _Multiplier = 1;

            // Set the current time RealTime
            _CurrentRealTime = time (NULL);
        }

        // Check for multiplier packages
        else if(data.isMember("multiplier"))
        {
            // get the multiplier
            _Multiplier = data["multiplier"].asInt();

            // DEBUG
            cout << "Time-multiplier: " << _Multiplier << endl;
        }

        // The received package is a light loop package
        else if(data.isMember("light"))
        {
            // Debug
            //cout << "Received loop package" << endl;

            // Assemble event package
            TRADEFS::SimulationQueueParticipant_t Event;
            Event.time  = _CurrentSimTime; /* Use the SimTime of the controller, of when the package arrived */
            Event.empty = data["empty"].asBool();
            Event.loop  = GetLoop ( data["loop"].asString());
            Event.type  = GetType ( data["type"].asString());

            // Split both Light and To in halfs
            string buffReceived, buffPartial;

            // First "from"/"light"
            buffReceived = data["light"].asString();
            buffPartial  = buffReceived.substr(0, 1);
            Event.fromDirection = GetDir( buffPartial);

            buffPartial    = buffReceived.substr(1, 2);
            Event.fromLane = atoi( buffPartial.c_str());

            // Second "to"
            buffReceived = data["to"].asString();
            buffPartial  = buffReceived.substr(0, 1);
            Event.toDirection = GetDir( buffPartial);

            buffPartial  = buffReceived.substr(1, 2);
            Event.toLane = atoi( buffPartial.c_str());

            _Arbitrator.AddEvent( Event);

            // Debug
            /*cout << data["type"].asString() << endl;
            cout << data["light"].asString() << endl;
            cout << data["loop"].asString() << endl;
            cout << data["empty"].asString() << endl;
            cout << data["to"].asString() << endl;

            cout << "[DEBUG] " << Event.fromLane << ", " << Event.toLane << endl;//*/
        }
        else
        {
            cout << "[Error] Received unknown package" << endl;
        }
    }
}

/* PackageMaster inverter functions follow here */
int GetLoop( string loop)
{
    // Compare
    if      ( loop.compare( "close") == 0)
        return 0;

    else if ( loop.compare( "far") == 0)
        return 1;

    else if ( loop.compare( "null") == 0)
        return -1;


    // All hell breaks loose!
    cout << "[ERROR] Unknown Loop Type! Abandon ship, it is sinking!" << endl;
    return -1;
}

TRADEFS::PARTICIPANTS GetType( string type)
{
    // Compare
    if      ( type.compare( "car") == 0)
        return TRADEFS::CAR;

    else if ( type.compare( "truck") == 0)
        return TRADEFS::CAR;

    else if ( type.compare( "godzilla") == 0)
        return TRADEFS::CAR;

    else if ( type.compare( "bus") == 0)
        return TRADEFS::BUS;

    else if ( type.compare( "pedestrian") == 0)
        return TRADEFS::PEDESTRIAN;

    else if ( type.compare( "bicycle") == 0)
        return TRADEFS::BIKE;


    // All hell breaks loose!
    cout << "[ERROR] Unknown Type! Abandon ship, it is sinking! Type: " << type << endl;
    return TRADEFS::CAR;
}

TRADEFS::DIRECTION GetDir( string dir)
{
    // Compare
    if      ( dir.compare( "N") == 0)
        return TRADEFS::NORTH;

    else if ( dir.compare( "S") == 0)
        return TRADEFS::SOUTH;

    else if ( dir.compare( "W") == 0)
        return TRADEFS::WEST;

    else if ( dir.compare( "E") == 0)
        return TRADEFS::EAST;


    // Compare
    cout << "[ERROR] Unknown Direction! Abandon ship, it is sinking!" << endl;
    return TRADEFS::NORTH;
}

TRADEFS::TRAFFICLIGHTSTATE GetLightState( string state)
{
    // Compare
    if ( state.compare( "green") == 0)
        return TRADEFS::PROCEED;

    else if ( state.compare( "red") == 0)
        return TRADEFS::STOP;

    else if ( state.compare( "yellow") == 0)
        return TRADEFS::STOP_ALMOST;

    else if ( state.compare( "blink") == 0)
        return TRADEFS::BLINKING;

    else if ( state.compare( "off") == 0)
        return TRADEFS::OFF;


    // Compare
    cout << "[ERROR] Unknown LightState! Abandon ship, it is sinking!" << endl;
    return TRADEFS::STOP;
}
