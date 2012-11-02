#ifndef CSIMULATIONVIEW_H
#define CSIMULATIONVIEW_H

#include "Camera.h"
#include "Skybox.h"
#include "CAbstractView.h"
#include "CStaticScene.h"

class CSimulationView : public CAbstractView
{
public:
    CSimulationView(int width, int height);

    void Init();

    void UpdatePull();
    void Update(float dt);
    void Draw();
    void Dispose();

    std::vector<SceneTrafficLight>&     GetTrafficLights(){ return trafficLights; }
    std::vector<SceneWayPoint>&         GetWaypoints() { return waypoints; }

private:
    Camera mCamera;
    Skybox mSkybox;
    CStaticScene mScene;
    int width, height;

    std::vector<SceneTrafficLight>  trafficLights;
    std::vector<SceneWayPoint>      waypoints;

    // mouse
    int mMoveSpeed;
    int mMidX, mMidY;
    int mMouseSensitivity;
};

#endif // CSIMULATIONVIEW_H
