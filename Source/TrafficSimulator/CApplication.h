#ifndef CAPPLICATION_H
#define CAPPLICATION_H

#include <iostream>
#include <fstream>

#include <GL/glfw.h>
#include <json/json-forwards.h>
#include <json/json.h>

#include "../../Source/TrafficSimulator/CSimulationController.h"
#include "../../Source/TrafficSimulator/CSimulationModel.h"

// Handles the creation of the application
class CApplication
{
public:
    CApplication() : mIsRunning( true), mWidth(0), mHeight(0), mModel(0), mController(0) {}

    bool Create(unsigned width, unsigned height);
    void Destroy();

    void AdvanceFrame();
    bool IsRunning() { return mIsRunning; }

private:
    void LoadInputFile(const char* fileName);

private:
    bool        mIsRunning;
    unsigned    mWidth, mHeight;

    CSimulationModel        *mModel;
    CSimulationController   *mController;
};

#endif // CAPPLICATION_H
