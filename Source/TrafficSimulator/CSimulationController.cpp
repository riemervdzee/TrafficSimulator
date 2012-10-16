#include "CSimulationController.h"
#include "CSimulationModel.h"
#include "CSimulationView.h"
#include "CNetworkView.h"

#include <iostream>
#include <fstream>

void CSimulationController::SetNetworkView(CNetworkView *view)
{
    if(view != 0)
    {
        view->SetController(this);
        view->SetModel(mModel);
    }

    if(mModel != 0)
        mModel->RegisterNetworkView(view);
}

void CSimulationController::SetSimulationView(CSimulationView *view)
{
    if(view != 0)
    {
        view->SetController(this);
        view->SetModel(mModel);
    }

    if(mModel != 0)
        mModel->RegisterSimulationView(view);
}

void CSimulationController::LoadInputFile(const char* fileName)
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

    /* JSON CODE
    // ###### JSON ########
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

    for(unsigned int i = 0; i < root.size(); ++i)
    {
        const Json::Value &element = root[i];
        std::cout << element["time"].asInt() << std::endl;
        std::cout << element["type"].asString() << std::endl;
        std::cout << element["from"].asString() << std::endl;
        std::cout << element["to"].asString() << std::endl;
    }
    */
}
