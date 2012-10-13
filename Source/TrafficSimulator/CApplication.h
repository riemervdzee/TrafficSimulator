#ifndef CAPPLICATION_H
#define CAPPLICATION_H

#include <iostream>
#include <fstream>

#include <GL/glfw.h>
#include <json/json-forwards.h>
#include <json/json.h>

// Handles the creation of the application
class CApplication
{
public:
    CApplication() : mIsRunning( true), mWidth(0), mHeight(0) {}

    bool Create(unsigned width, unsigned height);
    void Destroy();

    void AdvanceFrame();
    bool IsRunning() { return mIsRunning; }

private:
    void InitGraphics();
    void LoadInputFile(const char* fileName);

private:
    bool        mIsRunning;
    unsigned    mWidth, mHeight;
};

#endif // CAPPLICATION_H
