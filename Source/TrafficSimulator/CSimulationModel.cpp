#include "CSimulationModel.h"
#include "CSimulationView.h"
#include "CNetworkView.h"

#include <iostream>
#include <fstream>
#include <cstdlib>

CSimulationModel::CSimulationModel()
{
    mNetworkView = 0;
    mSimulationView = 0;
    simTime = 0;

    // init lanes
    laneGroups[TRADEFS::NORTH].SetDirectionType(TRADEFS::NORTH);
    laneGroups[TRADEFS::SOUTH].SetDirectionType(TRADEFS::SOUTH);
    laneGroups[TRADEFS::EAST].SetDirectionType(TRADEFS::EAST);
    laneGroups[TRADEFS::WEST].SetDirectionType(TRADEFS::WEST);
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

void CSimulationModel::UpdateSim()
{
    mTimer.Tick();
    float dt = mTimer.GetDeltaTime();
    simTime += dt;
    float timeCheck = simTime;

    // Get participants from the queue if appropiate
    while(simTime > (queue.top().time) && queue.size() > 0 )
    {
        SimulationQueueParticipant_t qPar = queue.top();
        printf("Got participant from queue! at %.2f\n", simTime);

        int parFront = laneGroups[qPar.fromDirection][qPar.fromLane]->GetParCount();
        laneGroups[qPar.fromDirection][qPar.fromLane]->IncCount();
        wmath::Vec3 startPos = laneGroups[qPar.fromDirection][qPar.fromLane]->GetWayStart();
        wmath::Vec3 endPos = laneGroups[qPar.fromDirection][qPar.fromLane]->GetWayEnd();
        wmath::Vec3 dir = startPos - endPos;
        dir.Norm();

        // if participants are coming at the same time align them behind each other
        if(simTime == timeCheck)
            startPos = startPos + dir * parFront * TRADEFS::CARSIZE;
        //printf("Par x: %f, y: %f, z: %f\n", startPos.x, startPos.y, startPos.z);

        // create participant
        CParticipant par = CParticipant(qPar.type, qPar.fromDirection, qPar.toDirection, qPar.fromLane, startPos, parFront);

        // set correct participant state depending on its type!
        if(par.GetType() != TRADEFS::PEDESTRIAN)
            par.SetState(TRADEFS::GOTOSTOPLIGHT);
        else
            par.SetState(TRADEFS::WAITATSTOPLIGHT);

        // add participant to pocessing list!
        participants.push_back(par);

        // TODO: send network update to the controller
        // participant crossed the first "loop"

        queue.pop();
    }

    // updateNetwork
    mNetworkView->UpdateNetwork();

    // update all participants
    UpdateParticipants(dt);

    // cleanup this frame
    std::vector<CParticipant>::iterator parIt = participants.begin();
    while(parIt != participants.end())
    {
        if(parIt->Remove())
        {
            printf("Removed participant!\n");
            parIt = participants.erase(parIt);
        }
        else ++parIt;
    }

    // process simulationview
    mSimulationView->Update( dt );
    mSimulationView->Draw();
}

void CSimulationModel::UpdateParticipants(float dt)
{
    for(unsigned int i = 0; i < participants.size(); i++)
    {
        CParticipant& par = participants[i];

        // do stuff based on the par state
        switch(par.GetState())
        {
            case TRADEFS::GOTOSTOPLIGHT:
                GoToStoplight(par, dt);
            break;
            case TRADEFS::WAITATSTOPLIGHT:
                WaitStoplight(par, dt);
            break;
            case TRADEFS::ONCROSSROAD:
                OnCrossroad(par, dt);
            break;
            case TRADEFS::GOTOEXIT:
                GoToExit(par, dt);
            break;
        }
    }
}

void CSimulationModel::GoToStoplight(CParticipant& par, float dt)
{
    wmath::Vec3 start = laneGroups[par.GetFrom()][par.GetLaneFrom()]->GetWayStart();
    wmath::Vec3 end = laneGroups[par.GetFrom()][par.GetLaneFrom()]->GetWayEnd();
    int paronlane = laneGroups[par.GetFrom()][par.GetLaneFrom()]->GetParCount();
    wmath::Vec3 laneDir = end - start;
    wmath::Vec3 parPos = par.GetPosition();
    wmath::Vec3 moveDir = (end - parPos);

    // get length between 2 lane waypoints, from start to end
    float laneLength = laneDir.Length();
    laneLength -= par.GetParInFront() * TRADEFS::CARSIZE;

    // get length between par pos and end waypoint
    float parLength = (parPos - start).Length();

    // check if we have reached our destination
    moveDir.Norm();
    laneDir.Norm();
    if(parLength > laneLength)
    {
        // set at the correct position
        //par.SetPosition(start + laneDir * laneLength);

        // change state
        par.SetState(TRADEFS::WAITATSTOPLIGHT);
    }
    else
    {
        // set it's new position
        par.SetPosition(parPos + moveDir * TRADEFS::CARSPEED * dt);
    }
}

void CSimulationModel::WaitStoplight(CParticipant& par, float dt)
{
    CTrafficLane* lane = laneGroups[par.GetFrom()][par.GetLaneFrom()];
    int lightID = lane->GetLightID();
    if(lightID != -1)
    {
        CTrafficLight light = trafficLights[lightID];
        par.SetState(TRADEFS::ONCROSSROAD);
        lane->DecCount();
    }
    else
    {
        par.SetState(TRADEFS::ONCROSSROAD);
        lane->DecCount();
    }
}

void CSimulationModel::OnCrossroad(CParticipant& par, float dt)
{
    wmath::Vec3 start = laneGroups[par.GetFrom()][par.GetLaneFrom()]->GetWayEnd();
    wmath::Vec3 end = laneGroups[par.GetTo()][TRADEFS::LANE_EXIT]->GetWayStart();
    wmath::Vec3 laneDir = end - start;
    wmath::Vec3 parPos = par.GetPosition();
    wmath::Vec3 moveDir = (end - parPos);

    // get length between 2 lane waypoints, from start to end
    float laneLength = laneDir.Length();

    // get length between par pos and end waypoint
    float parLength = (parPos - start).Length();

    // check if we have reached our destination
    laneDir.Norm();
    moveDir.Norm();
    if(parLength > laneLength)
    {
        // set at the correct position
        //par.SetPosition(start + laneDir * laneLength);

        // change state
        par.SetState(TRADEFS::GOTOEXIT);
    }
    else
    {
        // set it's new position
        par.SetPosition(parPos + moveDir * TRADEFS::CARSPEED * dt);
    }
}

void CSimulationModel::GoToExit(CParticipant& par, float dt)
{
    wmath::Vec3 start = laneGroups[par.GetTo()][TRADEFS::LANE_EXIT]->GetWayStart();
    wmath::Vec3 end = laneGroups[par.GetTo()][TRADEFS::LANE_EXIT]->GetWayEnd();
    wmath::Vec3 laneDir = end - start;
    wmath::Vec3 parPos = par.GetPosition();
    wmath::Vec3 moveDir = (end - parPos);

    // get length between 2 lane waypoints, from start to end
    float laneLength = laneDir.Length();

    // get length between par pos and end waypoint
    float parLength = (parPos - start).Length();

    // check if we have reached our destination
    laneDir.Norm();
    moveDir.Norm();
    if(parLength > laneLength)
    {
        par.FlagForRemoval();
    }
    else
    {
        // set it's new position
        par.SetPosition(parPos + moveDir * TRADEFS::CARSPEED * dt);
    }
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
        {
            laneGroups[laneG][lane]->SetWayStart(wmath::Vec3(pos.x, pos.y, pos.z));
        }
        else
        {
            laneGroups[laneG][lane]->SetWayEnd(wmath::Vec3(pos.x, pos.y, pos.z));
        }
    }

    // set trafficlights in the correct lane
    std::vector<SceneTrafficLight>& traL = mSimulationView->GetTrafficLights();

    for(unsigned int i = 0; i < traL.size(); ++i)
    {
        laneG = traL[i].laneGroup;
        lane = traL[i].lane;
        pos = traL[i].pos;

        // add light to the correct lane
        trafficLights.push_back(CTrafficLight( wmath::Vec3(pos.x , pos.y, pos.z) ));
        laneGroups[laneG][lane]->SetTrafficlight( trafficLights.size() - 1 );
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

void CSimulationModel::LoadParticipants(Json::Value& root)
{
    // load in all participants
    for(unsigned int i = 0; i < root.size(); ++i)
    {
        const Json::Value &element = root[i];
        SimulationQueueParticipant_t participant;

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

void CSimulationModel::ParseToLocation(const std::string& str, SimulationQueueParticipant_t& dest)
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

void CSimulationModel::ParseFromLocation(const std::string& str, SimulationQueueParticipant_t& dest)
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
