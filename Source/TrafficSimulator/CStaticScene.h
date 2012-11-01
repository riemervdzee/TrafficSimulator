#ifndef CSTATICSCENE_H
#define CSTATICSCENE_H

#include <vector>
#include <map>

#include "TDW/TDWFile.h"
#include "TDW/TDWLoader.h"

#include "Renderer/Buffers/IndexBuffer.h"
#include "Renderer/Buffers/VertexBuffer.h"
#include "Renderer/Shader.h"
#include "Renderer/Textures/Texture2D.h"

struct SceneVertex
{
    SceneVertex(vec3 pos, vec2 tex, vec2 lm)
    : position( pos ), texCoords(tex), lightmapCoords( lm ) {}

    vec3 position;
    vec2 texCoords;
    vec2 lightmapCoords;
};

struct DebugVertex
{
    DebugVertex(vec3 pos)
    {
        position = pos;
    }

    vec3 position;
};

class MaterialGroup
{
    public:
        MaterialGroup() : materialID(0) {}

        void AddVertex(SceneVertex vert) { vertexBuffer.push_back( vert ); }
        void AddIndex(unsigned short index) {  indexBuffer.push_back( index ); }
        int GetVertexCount() { return vertexBuffer.size(); }
        int GetMaterialID() { return materialID; }
        void SetMaterialID(int matid) { materialID = matid;}

        void BuildBuffers()
        {
            // build the vertexBuffer
            if(vertexBuffer.size() > 0)
                vertexBufferGPU.Create(&vertexBuffer[0], sizeof(SceneVertex) * vertexBuffer.size(), GL_STATIC_DRAW);

            // build the indexBuffer
            if(indexBuffer.size() > 0)
                indexBufferGPU.Create(&indexBuffer[0], indexBuffer.size(), GL_STATIC_DRAW);
        }

        void Draw()
        {
            vertexBufferGPU.Bind();
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);
            vertexBufferGPU.SetAttribPointer(0, 3, GL_FLOAT, sizeof(SceneVertex), 0 );
            vertexBufferGPU.SetAttribPointer(1, 2, GL_FLOAT, sizeof(SceneVertex), (void*)sizeof(vec3) );
            vertexBufferGPU.SetAttribPointer(2, 2, GL_FLOAT, sizeof(SceneVertex), (void*)(sizeof(vec3) + sizeof(vec2)) );

            indexBufferGPU.Bind();
            glDrawElements(GL_TRIANGLES, indexBuffer.size(), GL_UNSIGNED_SHORT, 0);
        }

        void Dispose()
        {
            vertexBufferGPU.Dispose();
            indexBufferGPU.Dispose();
        }
    private:
        int                             materialID;
        std::vector<SceneVertex>        vertexBuffer;
        std::vector<unsigned short>     indexBuffer;
        IndexBuffer                     indexBufferGPU;
        VertexBuffer                    vertexBufferGPU;
};

class Camera;
class CStaticScene
{
    public:
        bool Load(const char* fileName);
        void Dispose();
        void Draw(Camera* cam);

    private:
        ShaderProgram                   shader;
        std::vector<Texture2D>          materials;
        std::vector<TDWEntity>          cachedEntities;

        // DEBUG
        ShaderProgram                   debugShader;
        std::vector<DebugVertex>        debugVertices;
        VertexBuffer                    debugVertexBuffer;
        // DEBUG END

        typedef std::map< int, MaterialGroup > MaterialGroupMap;
        typedef std::map< int, MaterialGroupMap > RenderGroup;
        RenderGroup renderGroup;
};

#endif // CSTATICSCENE_H
