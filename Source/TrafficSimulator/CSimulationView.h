#ifndef CSIMULATIONVIEW_H
#define CSIMULATIONVIEW_H

#include "Camera.h"
#include "Skybox.h"
#include "CAbstractView.h"
#include "CStaticScene.h"

#include "../../Source/TrafficSimulator/Math/WildMath.h"

using wmath::Vec3;

struct dCube
{
    Vec3 position[36]; // cube
    Vec3 color[36];
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
            int w, int h, int d, Vec3 color, float rotation);

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
