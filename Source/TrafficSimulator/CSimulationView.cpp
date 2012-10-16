#include "CSimulationView.h"
#include "CSimulationController.h"
#include "CSimulationModel.h"

#include <GL/glfw.h>
#include <cmath>

#include "../../Source/TrafficSimulator/Math/WildMath.h"

using namespace wmath;

CSimulationView::CSimulationView(int width, int height)
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    	// init camera
	mCamera.Perspective(60.0f, (float)width / (float)height, 1.f, 100.0f);
	mCamera.LookAt(Vec3(0, 0, 0), Vec3(0, 0, 1), Vec3(0, 1, 0));

	// create skybox
	mSkybox.Init("Data\\textures\\miramar", &mCamera);
}

CSimulationView::~CSimulationView()
{
    mSkybox.Dispose();
}

void CSimulationView::UpdatePull()
{
    // get needed data from the model
}

void CSimulationView::Update(float dt)
{
    if( glfwGetKey( GLFW_KEY_ESC ) == GLFW_PRESS )
    {
        if(mController)
            mController->SetRunning(false);
    }

    float speed = 16.0;

    // speeding up
	if( glfwGetKey( GLFW_KEY_LSHIFT ) == GLFW_PRESS)
	{
		speed = speed * 4.0f;
	}

	// rotate
	int mX, mY;
	static int mLX = 0;
	static int mLY = 0;

	glfwGetMousePos(&mX, &mY);

	int mRX = mX - mLX;
	int mRY = mY - mLY;

    float yawSen = static_cast<float>(mRX) * dt;
    float pitchSen = static_cast<float>(mRY) * dt;

    mCamera.Rotate(pitchSen, yawSen , 0.0f);
    mLX = mX;
    mLY = mY;

    // move camera
	if(glfwGetKey( 's' ) == GLFW_PRESS)
	{
		mCamera.Move(speed * dt);
	}
	else if(glfwGetKey( 'w' ) == GLFW_PRESS)
	{
		mCamera.Move(-speed * dt);
	}

	// strafe camera
	if(glfwGetKey( 'a' ) == GLFW_PRESS)
	{
		mCamera.Strafe(-speed * dt);
	}
	else if(glfwGetKey( 'd' ) == GLFW_PRESS)
	{
		mCamera.Strafe(speed * dt);
	}
}

void CSimulationView::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mSkybox.Draw();

    glfwSwapBuffers();
}
