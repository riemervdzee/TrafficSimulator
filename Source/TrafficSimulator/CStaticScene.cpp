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
    printf("Loading materials!\n");
    std::vector<TDWMaterial>& mats = tdwFile->GetMaterials();
    for(int m = 0; m < mats.size(); ++m)
    {
        std::string texName = tdwFile->GetNameByIndex( mats[m].objectName - 1);

        Texture2D temp;
        temp.LoadTGA("Data\\Textures\\scene\\" + texName + ".tga", true);
        materials.push_back(temp);
    }

    // load lightmaps
    printf("Loading lightmaps!\n");
    std::vector<TDWLightmap>& lm = tdwFile->GetLightmaps();
    for(int m = 0; m < lm.size(); ++m)
    {
        Texture2D temp;
        temp.LoadFromMemory( (char*)lm[m].data, (char)lm[m].resolution);
        materials.push_back(temp);
    }

    // load entities

    // CONVERT BRUSHES TO USABLE POLYGONGROUPS
    printf("Loading geometry!\n");
    std::vector<TDWBrush>& brushes = tdwFile->GetBrushes();
    for(unsigned int b = 0; b < brushes.size(); ++b)
    {
        TDWBrush* brush = &brushes[b];
        TDWFace*  faces = brush->faces;
        unsigned int vCount = 0;
        int lmSubstract = tdwFile->GetGroupCount();

        // FACES
        for(int f = 0; f < brush->faceCount; ++f)
        {
            int lmID = faces[f].lightmapIndex - lmSubstract;
            int matID = faces[f].materialIndex;
            TDWIndex* indices = faces[f].indices;

            // check if there exist a rendergroup
            RenderGroup::const_iterator renderIter = renderGroup.find( lmID );
            if( renderIter == renderGroup.end() ) // rendergroup does not exist yet!
            {
                // add renderGroup and material group in that rendergroup
                MaterialGroupMap matGroupMap;
                matGroupMap[matID] = MaterialGroup();
                matGroupMap[matID].SetMaterialID(matID);
                renderGroup[lmID] = matGroupMap;
            }
            else // the rendergroup already exists
            {
                MaterialGroupMap& mgMap = renderGroup[lmID];
                MaterialGroupMap::iterator matIt = mgMap.find( matID );

                //if no materialGroup, add one
                if(matIt == mgMap.end() )
                {
                    mgMap[matID] = MaterialGroup();
                    mgMap[matID].SetMaterialID(matID);
                }
            }

            // add this faces vertices to the correct group
            vCount = renderGroup[lmID][matID].GetVertexCount();

            // add the vertices of this face
            for(int x = 0; x < faces[f].indexCount; x++)
            {
                TDWIndex* index = &indices[x];

                // add vertex to the correspondending materialGroup
                SceneVertex vertex(brush->vertices[index->vertex], index->texCoord, index->lightmapCoord);

                // add SceneVertex
                renderGroup[lmID][matID].AddVertex(vertex);
            }

            // Create triangles, from indexed triangle fan to indexed triangle list
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

    // dispose of all textures
    for(int i = 0; i < materials.size(); ++i)
    {
        materials[i].Dispose();
    }

    // dispose of the shaders
    shader.Dispose();
}

void CStaticScene::Draw(Camera* cam)
{
    shader.Bind();
    glFrontFace(GL_CCW);

    int texLoc =  glGetUniformLocation(shader.GetID(), "tex");
    int lmLock =  glGetUniformLocation(shader.GetID(), "lm");
    glUniform1i(texLoc, 0);
    glUniform1i(lmLock, 1);

    int projViewMatrix = glGetUniformLocation(shader.GetID(), "mvpMatrix");
    wmath::Mat4 projView = cam->GetProjection() * cam->GetView();
    glUniformMatrix4fv(projViewMatrix, 1, GL_FALSE, (GLfloat*)&projView);

    // iterate all rendergroups and draw them
    for(RenderGroup::iterator rgIt = renderGroup.begin(); rgIt != renderGroup.end(); ++rgIt)
    {
        int lmID = rgIt->first;

        // bind the used lightmap
        if(lmID != 0)
        {
            materials[lmID - 1].Bind(1);
        }

        // iterate all materialgroups inside this rendergroup
        for(MaterialGroupMap::iterator mgIt = rgIt->second.begin(); mgIt != rgIt->second.end(); ++mgIt)
        {
            // bind the used texture
            materials[mgIt->second.GetMaterialID() - 1].Bind(0);

            // buildbuffers
            mgIt->second.Draw();
        }
    }

    shader.Unbind();
}
