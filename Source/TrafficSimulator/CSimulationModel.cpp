#include "CSimulationModel.h"
#include "CSimulationView.h"
#include "CNetworkView.h"
#include "TDW/TDWDefs.h"

#include <iostream>
#include <fstream>

CSimulationModel::CSimulationModel()
{
    mNetworkView = 0;
    mSimulationView = 0;
    mTimer.Create();

    // init lanes
    laneGroups[0].SetDirectionType(0); // NORTH
    laneGroups[1].SetDirectionType(1); // SOUTH
    laneGroups[2].SetDirectionType(2); // EAST
    laneGroups[3].SetDirectionType(3); // WEST
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
        laneGroups[laneG][lane]->SetTrafficlight( CTrafficLight( wmath::Vec3(pos.x , pos.y, pos.z) ) );
    }
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

    // load in all participants
    for(unsigned int i = 0; i < root.size(); ++i)
    {
        const Json::Value &element = root[i];
        CSimulationQueueParticipant participant;
        participant.time = element["time"].asInt();
        std::cout << element["time"].asInt() << std::endl;
        std::cout << element["type"].asString() << std::endl;
        std::cout << element["from"].asString() << std::endl;
        std::cout << element["to"].asString() << std::endl;
    }
}

