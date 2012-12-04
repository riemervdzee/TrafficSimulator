#ifndef CSIMULATIONVIEW_H
#define CSIMULATIONVIEW_H

#include "Camera.h"
#include "Skybox.h"
#include "CAbstractView.h"
#include "CStaticScene.h"

#include "../../Source/TrafficSimulator/Math/WildMath.h"

using wmath::Vec3;

struct cubeVert
{
    Vec3 position;
    Vec3 color;
};

struct dCube
{
    cubeVert verts[36];
};

class CSimulationView : public CAbstractView
{
public:
    CSimulationView(int width, int height);

    void Init();

    void Update(float dt);
    void Draw();
    void Dispose();

    std::vector<SceneTrafficLight>&     GetTrafficLights(){ return trafficLights; }
    std::vector<SceneWayPoint>&         GetWaypoints() { return waypoints; }

private:
    void DrawLights();
    void DrawParticipants();
    
    // creates a cube for trafficlights and participants
    void addCube(dCube& cube, Vec3 pos, 
            float w, float h, float d, Vec3 color, float rotation, Vec3 extr);

private:
    Camera mCamera;
    Skybox mSkybox;
    CStaticScene mScene;
    int width, height;

    std::vector<SceneTrafficLight>  trafficLights;
    std::vector<SceneWayPoint>      waypoints;

    // participant drawing
    ShaderProgram   parShader;
    VertexBuffer    parVertexBuffer;
    
    
    // trafficlight drawin
    ShaderProgram   traShader;
    VertexBuffer    traVertexBuffer;

    // mouse
    int mMoveSpeed;
    int mMidX, mMidY;
    int mMouseSensitivity;
};

#endif // CSIMULATIONVIEW_H
