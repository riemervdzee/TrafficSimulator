#include "CStaticScene.h"
#include "../../Source/TrafficSimulator/Camera.h"
#include "../../Source/TrafficSimulator/Math/WildMath.h"
#include "../../Source/TrafficSimulator/Util.h"
#include <set>

bool CStaticScene::Load(const char* fileName)
{
    TDWFile* tdwFile = 0;
    tdwFile = TDWLoader::LoadFromFile(fileName);

    if(tdwFile == 0)
        return false;

    printf("Building the scene!\n");

    // load materials

    // load lightmaps

    // load entities

    // CONVERT BRUSHES TO USABLE POLYGONGROUPS
    std::vector<TDWBrush>& brushes = tdwFile->GetBrushes();

    // BRUSHES
    for(unsigned int b = 0; b < brushes.size(); ++b)
    {
        TDWBrush* brush = &brushes[b];
        TDWFace*  faces = brush->faces;
        unsigned int vCount = 0;

        printf("VertexCount: %d\n", brush->vertexCount);
        for(int x = 0; x < brush->vertexCount; ++x)
        {
            printf("[%d] - X: %.1f, Y: %.1f, Z: %.1f\n", x, brush->vertices[x].x, brush->vertices[x].y, brush->vertices[x].z);
        }

        // FACES
        for(int f = 0; f < brush->faceCount; ++f)
        {
            int lmID = faces[f].lightmapIndex;
            int matID = faces[f].materialIndex;
            TDWIndex* indices = faces[f].indices;

            // check if there exist a rendergroup
            RenderGroup::const_iterator renderIter = renderGroup.find( lmID );
            if( renderIter == renderGroup.end() ) // rendergroup does not exist yet!
            {
                // add renderGroup and material group in that rendergroup
                MaterialGroupMap matGroupMap;
                matGroupMap[matID] = MaterialGroup();
                renderGroup[lmID] = matGroupMap;
            }
            else // the rendergroup already exists
            {
                MaterialGroupMap& mgMap = renderGroup[lmID];
                MaterialGroupMap::iterator matIt = mgMap.find( matID );

                //if no materialGroup, add one
                if(matIt == mgMap.end() )
                    mgMap[matID] = MaterialGroup();
            }

            // add the vertices of this face
            for(int x = 0; x < faces[f].indexCount; x++)
            {
                TDWIndex* index = &indices[x];

                // add vertex to the correspondending materialGroup
                SceneVertex vertex(brush->vertices[index->vertex], index->texCoord, index->lightmapCoord);

                // add SceneVertex
                renderGroup[lmID][matID].AddVertex(vertex);
            }


            // add this faces vertices to the correct group
            vCount = renderGroup[lmID][matID].GetVertexCount();

            // Create triangles, from triangle fan to triangle list
            for(int i = 1; i < faces[f].indexCount - 1; ++i)
            {
                renderGroup[lmID][matID].AddIndex(vCount + 0);
                renderGroup[lmID][matID].AddIndex(vCount + i );
                renderGroup[lmID][matID].AddIndex(vCount + i + 1);
            }
        }
    }

    // iterate all rendergroups and build the GPU buffers
    for(RenderGroup::iterator rgIt = renderGroup.begin(); rgIt != renderGroup.end(); ++rgIt)
    {
        // iterate all materialgroups inside this rendergroup
        for(MaterialGroupMap::iterator mgIt = rgIt->second.begin(); mgIt != rgIt->second.end(); ++mgIt)
        {
            // buildbuffers
            mgIt->second.BuildBuffers();
        }
    }

    // shader data
    std::string vertex;
    std::string fragment;

    // creating shaders
    LoadTextFile("Data\\shaders\\scene.vert", vertex);
    LoadTextFile("Data\\shaders\\scene.frag", fragment);

    // load shaders
    shader.CreateProgram(vertex, fragment);

    // free memory
    delete tdwFile;
    tdwFile = 0;

    return true;
}

void CStaticScene::Dispose()
{
    // iterate all rendergroups and dispose of the material groups
    for(RenderGroup::iterator rgIt = renderGroup.begin(); rgIt != renderGroup.end(); ++rgIt)
    {
        // iterate all materialgroups inside this rendergroup
        for(MaterialGroupMap::iterator mgIt = rgIt->second.begin(); mgIt != rgIt->second.end(); ++mgIt)
        {
            // buildbuffers
            mgIt->second.Dispose();
        }
    }
}

void CStaticScene::Draw(Camera* cam)
{
    shader.Bind();

    int projViewMatrix = glGetUniformLocation(shader.GetID(), "mvpMatrix");
    wmath::Mat4 projView = cam->GetProjection() * cam->GetView();
    glUniformMatrix4fv(projViewMatrix, 1, GL_FALSE, (GLfloat*)&projView);

    // iterate all rendergroups and draw them
    for(RenderGroup::iterator rgIt = renderGroup.begin(); rgIt != renderGroup.end(); ++rgIt)
    {
        // iterate all materialgroups inside this rendergroup
        for(MaterialGroupMap::iterator mgIt = rgIt->second.begin(); mgIt != rgIt->second.end(); ++mgIt)
        {
            // buildbuffers
            mgIt->second.Draw();
        }
    }

    shader.Unbind();
}
