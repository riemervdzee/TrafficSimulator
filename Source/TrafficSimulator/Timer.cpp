/*
 * Author: Mark van der Wal
 * Date: 30-10-2011
 * Descr: High performance timer class
 */
#include "Timer.h"

void CTimer::Create()
{
    // gets the time in milliseconds
    mPrevTime = static_cast<float>( glfwGetTime() );
    mTimeScale = 0.001;
}

void CTimer::Tick()
{
    float curTime;
    curTime = static_cast<float>( glfwGetTime() );
    mDeltaTime =  (curTime - mPrevTime) * static_cast<float>( mTimeScale );
    mPrevTime = curTime;
}
