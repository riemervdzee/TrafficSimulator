#ifndef CSIMULATIONVIEW_H
#define CSIMULATIONVIEW_H

#include "Camera.h"
#include "Skybox.h"
#include "CAbstractView.h"

class CSimulationView : public CAbstractView
{
public:
    CSimulationView(int width, int height);
    ~CSimulationView();

    void UpdatePull();
    void Update(float dt);
    void Draw();

private:
    Camera mCamera;
    Skybox mSkybox;
    int width, height;

    // mouse
    int mMoveSpeed;
    int mMidX, mMidY;
    int mMouseSensitivity;
};

#endif // CSIMULATIONVIEW_H
