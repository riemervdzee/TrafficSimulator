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
    vec3 position;
    vec2 texCoords;
    vec2 lightmapCoords;
};

class MaterialGroup
{
    public:
        MaterialGroup() : materialID(0) {}

        void AddVertex(SceneVertex vert);
        void AddIndex(short index);

        void BuildBuffers();

        int GetVertexBufferSize() { vertexBuffer.size(); }
        int GetIndexBufferSize() { indexBuffer.size(); }

        void Dispose();
    private:
        int                         materialID;
        std::vector<SceneVertex>    vertexBuffer;
        std::vector<short>          indexBuffer;
        IndexBuffer                 indexBufferGPU;
        VertexBuffer                VertexBufferGPU;
};

class Camera;
class CStaticScene
{
    public:
        CStaticScene()
        : loaded( false) {}

        bool Load(const char* fileName);
        void Dispose();
        void Draw(Camera* cam);

    private:
        bool                                            loaded;
        ShaderProgram                                   shader;
        std::vector<Texture2D>                          lightmaps;
        std::vector<Texture2D>                          materials;

        typedef std::map< int, MaterialGroup > MaterialGroupMap;
        typedef std::multimap< int, MaterialGroupMap > RenderGroup;
        RenderGroup renderGroup;
};

#endif // CSTATICSCENE_H
