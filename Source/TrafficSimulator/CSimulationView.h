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
    ~CSimulationView();

    void Init();

    void UpdatePull();
    void Update(float dt);
    void Draw();

private:
    Camera mCamera;
    Skybox mSkybox;
    CStaticScene mScene;
    int width, height;

    // mouse
    int mMoveSpeed;
    int mMidX, mMidY;
    int mMouseSensitivity;
};

#endif // CSIMULATIONVIEW_H
