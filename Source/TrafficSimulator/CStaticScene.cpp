#include "CStaticScene.h"

bool CStaticScene::Load(const char* fileName)
{
    TDWFile* tdwFile = 0;
    tdwFile = TDWLoader::LoadFromFile(fileName);

    if(tdwFile == 0)
        return false;

    // load materials

    // load lightmaps

    // load entities

    // CONVERT BRUSHES TO USABLE POLYGONS
    std::vector<TDWBrush>& brushes = tdwFile->GetBrushes();
    int matID = 0;
    int lmID = 0;
    TDWIndex* indices = 0;

    // iterate over all brushes
    for(unsigned int i = 0; i < brushes.size(); ++i)
    {
        TDWBrush* brush = &brushes[i];
        TDWFace*  faces = brush->faces;

        // iterate over all faces the brush has
        for(int j = 0; j < brush->faceCount; ++j)
        {
            lmID = faces[j].lightmapIndex;
            matID = faces[j].materialIndex;
            indices = faces[j].indices;

            // check if there exist a rendergroup
            RenderGroup::const_iterator renderIter = renderGroup.find( lmID );
            if( renderIter == renderGroup.end() ) // rendergroup does not exist yet!
            {
                // add renderGroup and material group in that rendergroup
                MaterialGroupMap matGroupMap;
                matGroupMap[matID] = MaterialGroup();
                renderGroup.insert( RenderGroup::value_type(lmID, matGroupMap) );
            }
            else // rendergroup exists
            {
                // check if a material group exists within the rendergroup
                int renderGroupCount = renderGroup.count( lmID );
                for(int a = 0; a < renderGroupCount; ++a)
                {
                    if( renderIter->second.find(matID) != renderIter->second.end() )
                        break;

                    ++renderIter;
                }

                //if no materialGroup has been found in the renderGroup
                if(renderIter == renderGroup.end() )
                {
                    // add a materialGroup
                    MaterialGroupMap matGroupMap;
                    matGroupMap[matID] = MaterialGroup();
                    renderGroup.insert( RenderGroup::value_type(lmID, matGroupMap));
                }
            }

            // now we can add vertices and indices
            for(int k = 0; k < faces[j].indexCount; ++k)
            {
                TDWIndex* index = &indices[k];

                // add vertex to the correspondending materialGroup
                SceneVertex vertex;
                vertex.position = brush->vertices[index->vertex];
                vertex.texCoords = index->texCoord;
                vertex.lightmapCoords = index->lightmapCoord;

                // get the rendergroup we need
                RenderGroup::const_iterator renderIter = renderGroup.find( lmID );
                int renderGroupCount = renderGroup.count( lmID );
                for(int a = 0; a < renderGroupCount; ++a)
                {
                    if( renderIter->second.find(matID) != renderIter->second.end() )
                        break;

                    ++renderIter;
                }

                // add SceneVertex
                renderIter->second[matID]->AddVertex(vertex);
                renderIter->second[matID]->AddIndex(k);
            }
        }
    }

    // free memory
    delete tdwFile;
    tdwFile = 0;

    return true;
}

void CStaticScene::Dispose()
{

}

void CStaticScene::Draw(Camera* cam)
{


}
