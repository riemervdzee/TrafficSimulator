#ifndef CSIMULATIONVIEW_H
#define CSIMULATIONVIEW_H

#include "../../Source/TrafficSimulator/CAbstractView.h"
#include "../../Source/TrafficSimulator/Camera.h"
#include "../../Source/TrafficSimulator/Skybox.h"

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
};

#endif // CSIMULATIONVIEW_H
