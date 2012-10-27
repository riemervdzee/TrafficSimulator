/*
 * Author: Mark van der Wal
 * Date: 30-10-2011
 * Descr: High performance timer class
 */
#ifndef _TIMER_H_
#define _TIMER_H_

#include <GL/glew.h>
#include <GL/glfw.h>

// High performance timer used in real time enviroments
class CTimer
{
public:
	// constructor/destructor
	CTimer(): mDeltaTime(0.0), mPrevTime(0.0) {}

	// management
	void Create();

	// update the timer every frame
	void Tick();

	// getters
	double GetDeltaTime() const { return mDeltaTime; }

private:
	double mDeltaTime;
	double mPrevTime;
};

#endif //_CTIMER_H_
