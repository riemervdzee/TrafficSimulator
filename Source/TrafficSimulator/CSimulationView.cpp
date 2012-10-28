#include "CSimulationView.h"
#include "CSimulationController.h"
#include "CSimulationModel.h"

#include <GL/glfw.h>
#include <cmath>

#include "../../Source/TrafficSimulator/Math/WildMath.h"

using namespace wmath;

CSimulationView::CSimulationView(int width, int height)
{
    this->width = width;
    this->height = height;

    // middle of the screen
    mMidX = width / 2;
    mMidY = height / 2;
}

CSimulationView::~CSimulationView()
{
    mSkybox.Dispose();
}

void CSimulationView::Init()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    mMoveSpeed = 15;
    glfwSetMousePos(mMidX, mMidY);
    glfwDisable( GLFW_MOUSE_CURSOR );
    mMouseSensitivity = 5.0f;

    // init camera
	mCamera.Perspective(60.0f, (float)width / (float)height, 1.f, 100.0f);
	mCamera.LookAt(Vec3(0, 0, 0), Vec3(0, 0, 1), Vec3(0, 1, 0));

	// create skybox
	mSkybox.Init("Data\\textures\\miramar", &mCamera);

    // load the scene
    mScene.Load("Data\\crossroad.3dw");
}

void CSimulationView::UpdatePull()
{
    // get needed data from the model
}

void CSimulationView::Update(float dt)
{
    // SHUTDOWN SIMULATION
    if( glfwGetKey( GLFW_KEY_ESC ) == GLFW_PRESS  )
    {
        if(mController >= 0)
            mController->SetRunning(false);
    }

    int speed = mMoveSpeed;

    // PRESS SHIFT FOR SPEED UP
	if( glfwGetKey( GLFW_KEY_LSHIFT ) == GLFW_PRESS)
	{
		speed = mMoveSpeed * 4.0f;
	}

    // ########## CAMERA MOUSE MOVEMENT ###########
    int mX, mY;
    int mdX, mdY;
	glfwGetMousePos(&mX, &mY);
	glfwSetMousePos(width / 2, height / 2);

	mdX = mX - mMidX;
	mdY = mY - mMidY;

    mCamera.Rotate(static_cast<float>(mdY) * dt * mMouseSensitivity, static_cast<float>(mdX) * dt * mMouseSensitivity, 0.0f);
    // ########## END CAMERA MOUSE MOVEMENT ###########

    // ########## CAMERA KEYBOARD MOVEMENT ###########
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
	// ########## END CAMERA KEYBOARD MOVEMENT ###########
}

void CSimulationView::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw scene

    // draw trafficlights

    // draw participants

    // draw skybox
    mSkybox.Draw();

    glfwSwapBuffers();
}
