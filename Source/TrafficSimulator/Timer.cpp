/*
 * Author: Mark van der Wal
 * Date: 30-10-2011
 * Descr: High performance timer class
 */
#include "Timer.h"

void CTimer::Create()
{
    // gets the time in milliseconds
    mPrevTime = glfwGetTime();
}

void CTimer::Tick()
{
    double curTime = glfwGetTime();
    mDeltaTime = (curTime - mPrevTime);
    mPrevTime = curTime;
}
