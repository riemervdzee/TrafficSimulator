#ifndef CAPPLICATION_H
#define CAPPLICATION_H

#include <GL/glew.h>
#include <GL/glfw.h>
#include <json/json-forwards.h>
#include <json/json.h>

class CSimulationController;
class CSimulationModel;

// Handles the creation of the application
class CApplication
{
public:
    CApplication() : mWidth(0), mHeight(0), mModel(0), mController(0) {}

    bool Create(unsigned width, unsigned height);
    void Destroy();

    void AdvanceFrame();
    bool IsRunning();

private:
    unsigned    mWidth, mHeight;

    CSimulationModel        *mModel;
    CSimulationController   *mController;
};

#endif // CAPPLICATION_H
