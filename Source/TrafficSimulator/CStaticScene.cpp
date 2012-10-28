#include "CStaticScene.h"
#include "TDW/TDWFile.h"
#include "TDW/TDWLoader.h"

bool CStaticScene::Load(const char* fileName)
{
    TDWFile* tdwFile = 0;
    tdwFile = TDWLoader::LoadFromFile(fileName);

    if(tdwFile == 0)
        return false;

    // convert brushes to usable data for renderer

    // get entities

    // free memory
    delete tdwFile;
    tdwFile = 0;

    return true;
}

void CStaticScene::Dispose()
{

}

void CStaticScene::Draw()
{


}
