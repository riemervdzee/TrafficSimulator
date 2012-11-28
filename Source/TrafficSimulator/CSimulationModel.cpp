#include "CSimulationModel.h"
#include "CSimulationView.h"
#include "CNetworkView.h"
#include "PacketMaster.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

CSimulationModel::CSimulationModel()
{
    mNetworkView = 0;
    mSimulationView = 0;
    simTime = 0;
    speedMultiplier = 1;
    mSimStarted = false;
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
        // init the simulation view
        mSimulationView = observer;
        mSimulationView->Init();

        // load entities
        LoadEntities();

        // create timer
        mTimer.Create();
    }
}

void CSimulationModel::Connected()
{
    mSimStarted = true;
    
    // send init message
    if(mNetworkView != 0)
    {
        // send init messsage
        mNetworkView->SendString( PacketMaster::GetInitPackage(queue.top().time, speedMultiplier));
    }
}

void CSimulationModel::Disconnected()
{
    mSimStarted = false;
    
    // clear queue
    queue = std::priority_queue<TRADEFS::SimulationQueueParticipant_t>();
    
    // clear other
    trafficLights.clear();
    participants.clear();
    
    // clear Lanes
    for(int i = 0; i < 4; i++)
    {
        laneGroups[i].Clear();
    }
    
    // load input file again
    LoadInputFromFile("Data/inputFile.json");
}

void CSimulationModel::UpdateSim()
{
    mTimer.Tick();
    float dt = dt = mTimer.GetDeltaTime();
    
    if(mSimStarted)
    {
        simTime += dt;

        // Get participants from the queue if appropiate
        while(simTime > ((queue.top()).time) && !queue.empty() )
        {
            // get participant from the top
            const TRADEFS::SimulationQueueParticipant_t& qPar = queue.top();

            // Easier to use lane type
            CTrafficLane* lane = laneGroups[qPar.fromDirection][qPar.fromLane];
            lane->AddParticipant(participants, qPar);

            // TODO: send network update to the controller
            // participant crossed the first "loop"
            if(mNetworkView != 0)
            {
                // create package
                std::string pack = PacketMaster::GetLoopPackage(qPar.fromDirection, qPar.fromLane, qPar.type, 0,
                        false, qPar.toDirection, qPar.toLane);

                // send package
                mNetworkView->SendString(pack);
            }

            queue.pop();
        }

        // updateNetwork, get light messages, process
        mNetworkView->UpdateNetwork();

        // update all participants
        UpdateParticipants(dt);

        // cleanup this frame
        std::list<CParticipant>::iterator parIt = participants.begin();
        while(parIt != participants.end())
        {
            if(parIt->Remove())
            {
                parIt = participants.erase(parIt);
            }
            else ++parIt;
        }
    }

    // process simulationview
    mSimulationView->Update( dt );
    mSimulationView->Draw();
}

void CSimulationModel::UpdateParticipants(float dt)
{
    // iterate over all groups
    // Only responsable for the incoming and waiting participants
    for(int i = 0; i < TRADEFS::MAXGROUPS; ++i)
    {
        for(int j = 0; j < TRADEFS::MAXLANES; ++j)
        {
            // update
            laneGroups[i][j]->UpdateParticipants(trafficLights, laneGroups, dt);
        }
    }

    // update participants that have passed trafficlights
}

void CSimulationModel::LoadEntities()
{
    // set waypoints in the correct lane
    std::vector<SceneWayPoint>& wayP = mSimulationView->GetWaypoints();
    int lane = 0;
    int laneG = 0;
    int type = 0;
    vec3 pos;

    for(unsigned int i = 0; i < wayP.size(); ++i)
    {
        laneG = wayP[i].laneGroup;
        lane = wayP[i].lane;
        type = wayP[i].wayType;
        pos = wayP[i].pos;

        // add waypoint to the correct lane
        if( type == 0)
            laneGroups[laneG][lane]->SetWayStart(wmath::Vec3(pos.x, pos.y, pos.z));
        else if ( type == 1)
            laneGroups[laneG][lane]->SetWayEnd(wmath::Vec3(pos.x, pos.y, pos.z));
        else // type is pedestrianStart (type=2)
        {
            ((CPedestrianTrafficLane*)laneGroups[laneG][lane])->SetPedStart(wmath::Vec3(pos.x, pos.y, pos.z));
        }
    }

    // set trafficlights in the correct lane
    std::vector<SceneTrafficLight>& traL = mSimulationView->GetTrafficLights();

    for(unsigned int i = 0; i < traL.size(); ++i)
    {
        laneG = traL[i].laneGroup;
        lane = traL[i].lane;
        pos = traL[i].pos;

        if(lane == 8) // special light for pedestrians in the middle used by 2 lanes
        {

            trafficLights.push_back(CTrafficLight( wmath::Vec3(pos.x , pos.y, pos.z) ));
            ((CPedestrianTrafficLane*)laneGroups[laneG][TRADEFS::LANE_PEDESTRIAN_ONE])->SetMidTrafficlight( trafficLights.size() - 1 );
            ((CPedestrianTrafficLane*)laneGroups[laneG][TRADEFS::LANE_PEDESTRIAN_TWO])->SetMidTrafficlight( trafficLights.size() - 1 );
        }
        else
        {

            // add light to the correct lane
            trafficLights.push_back(CTrafficLight( wmath::Vec3(pos.x , pos.y, pos.z) ));
            laneGroups[laneG][lane]->SetTrafficlight( trafficLights.size() - 1 );
        }
    }
}

void CSimulationModel::LoadInputFromFile(const char* fileName)
{
    std::ifstream file;
    std::string fileData;
    file.open(fileName);

    if(!file.is_open())
    {
        std::cout << "Can't open the specified file\n";
        return;
    }

    // read in string
    std::string line;
    while( !file.eof() )
    {
        getline( file, line);
        fileData += line + "\n";
    }

    file.close();

    Json::Value root;   // will contains the root value after parsing.
    Json::Reader reader;
    bool parsingSuccessful = reader.parse( fileData, root );
    if ( !parsingSuccessful )
    {
        // report to the user the failure and their locations in the document.
        std::cout  << "Failed to parse configuration\n"
                   << reader.getFormattedErrorMessages();
        return;
    }

    std::cout << "===============================\n";
    std::cout << "Loaded inputfile!\n";
    LoadParticipants(root);

    std::cout << "Added " << queue.size() << " participants to the Queue\n" << std::endl;
    std::cout << "===============================\n";
}

void CSimulationModel::ParseLocation(const std::string& str, int& dir, int& lane)
{
    int size = str.size();

    if( size > 2 || size < 1)
        return;

    if( size == 2)
    {
        // check direction
        dir = GetDirection(str[0]);

        // check lane
        lane = GetLane(str[1]);

    }
    else
    {
       // check direction
       dir = GetDirection(str[0]);
    }
}

void CSimulationModel::ParseLightState(const std::string& str, int& state)
{
    if(str.compare("green") == 0)
    {
        state = TRADEFS::PROCEED;
    }
    else if(str.compare("red") == 0)
    {
        state = TRADEFS::STOP;
    }
    else if(str.compare("yellow") == 0)
    {
        state = TRADEFS::STOP_ALMOST;
    }
    else if(str.compare("blink") == 0)
    {
        state = TRADEFS::BLINKING;
    }
    else if(str.compare("off") == 0)
    {
        state = TRADEFS::OFF;
    }
    else
    {
        state = -1;
    }
}

void CSimulationModel::ProcessMsg(const Json::Value& data)
{
    // handle msg
    if( data.isMember("light") )
    {
        int dir, lane, state;
        
        std::string lightLocation = data["light"].asString();
        std::string lightState = data["state"].asString();
        
        // parse strings
        ParseLocation(lightLocation, dir, lane);
        ParseLightState(lightState, state);
        
        if((dir >= 0 && dir < 4) && (lane >= 0 && lane < 8))
        {
            // change state of the corresponding light
            int lightID = laneGroups[dir][lane]->GetLightID();
            trafficLights.at(lightID).SetState((TRADEFS::TRAFFICLIGHTSTATE)state);
        }
        else
        {
            std::cout << "Could not process network light update!" << std::endl;
        }
    }
}

void CSimulationModel::LoadParticipants(Json::Value& root)
{
    // load in all participants
    for(unsigned int i = 0; i < root.size(); ++i)
    {
        const Json::Value &element = root[i];
        TRADEFS::SimulationQueueParticipant_t participant;
        memset((void*)&participant, 0, sizeof(participant));

        // create participant
        participant.time = element["time"].asInt();

        // check which type
        std::string type = element["type"].asString();
        if(type.compare("car") == 0)
        {
            participant.type = TRADEFS::CAR;
        }
        else if(type.compare("bike") == 0)
        {
            participant.type = TRADEFS::BIKE;
        }
        else if(type.compare("pedestrian") == 0)
        {
            participant.type = TRADEFS::PEDESTRIAN;
        }
        else if(type.compare("bus") == 0)
        {
            participant.type = TRADEFS::BUS;
        }

        // get lanegroup and lane
        ParseFromLocation(element["from"].asString(), participant);
        ParseToLocation(element["to"].asString(), participant);

        // push into the queue
        queue.push(participant);
    }
}

void CSimulationModel::ParseToLocation(const std::string& str, TRADEFS::SimulationQueueParticipant_t& dest)
{
    int size = str.size();

    if( size > 2 || size < 1)
        return;

    if( size == 2)
    {
        // check direction
        dest.toDirection = GetDirection(str[0]);

        // check lane
        dest.toLane = GetLane(str[1]);

    }
    else
    {
       // check direction
       dest.toDirection = GetDirection(str[0]);
    }

}

void CSimulationModel::ParseFromLocation(const std::string& str, TRADEFS::SimulationQueueParticipant_t& dest)
{
    int size = str.size();

    if( size > 2 || size < 1)
        return;

    if( size == 2)
    {
        // check direction
        dest.fromDirection = GetDirection(str[0]);

        // check lane
        dest.fromLane = GetLane(str[1]);
    }
    else
    {
       // check direction
       dest.fromDirection = GetDirection(str[0]);
    }

}

TRADEFS::DIRECTION CSimulationModel::GetDirection(const char val)
{
    switch(val)
    {
        case 'N':
            return TRADEFS::NORTH;
        case 'S':
            return TRADEFS::SOUTH;
        case 'E':
            return TRADEFS::EAST;
        case 'W':
            return TRADEFS::WEST;
        default: return TRADEFS::NORTH;
    }
}

int CSimulationModel::GetLane(char val)
{
    return atoi(&val);
}
