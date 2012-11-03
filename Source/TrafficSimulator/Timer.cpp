/*
 * Author: Mark van der Wal
 * Date: 30-10-2011
 * Descr: High performance timer class
 */
#include "Timer.h"

double CTimer::Create()
{
    // gets the time in milliseconds
    return mPrevTime = glfwGetTime();
}

void CTimer::Tick()
{
    double curTime = glfwGetTime();
    mDeltaTime = (curTime - mPrevTime);
    mPrevTime = curTime;
}
