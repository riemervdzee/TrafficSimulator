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

void CSimulationView::Dispose()
{
    mSkybox.Dispose();
    mScene.Dispose();
}

void CSimulationView::Init()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_TEXTURE_2D);

    mMoveSpeed = 64.0f;
    glfwSetMousePos(mMidX, mMidY);
    glfwDisable( GLFW_MOUSE_CURSOR );
    mMouseSensitivity = 8.0f;

    // init camera
	mCamera.Perspective(60.0f, (float)width / (float)height, 1.f, 400.0f);
	mCamera.LookAt(Vec3(32, 64, -32), Vec3(0, 32.0f, 1), Vec3(0, 1, 0));

	// create skybox
	mSkybox.Init("Data\\textures\\miramar", &mCamera);

    // load the scene
    mScene.Load("Data\\crossroad.3dw", trafficLights, waypoints);

    // load shader for participant
    std::string dvertex;
    std::string dfragment;

    // creating shaders
    LoadTextFile("Data\\shaders\\tra_col.vert", dvertex);
    LoadTextFile("Data\\shaders\\tra_col.frag", dfragment);

    // load shaders
    parShader.CreateProgram(dvertex, dfragment);

    // create buffer for participants
    parVertexBuffer.Create(sizeof(wmath::Vec3) * 128, GL_DYNAMIC_DRAW);
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

    // debug
    static bool last = false; // lazy HACK! :P
    if( glfwGetKey( 'L') == GLFW_PRESS) last = true;
    if( glfwGetKey( 'L') == GLFW_RELEASE && last == true)
	{
		mScene.ToggleDebug();
		last = false;
	}

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
	if(glfwGetKey( 'S' ) == GLFW_PRESS)
	{
		mCamera.Move(-speed * dt);
	}
	else if(glfwGetKey( 'W' ) == GLFW_PRESS)
	{
		mCamera.Move(speed * dt);
	}

	// strafe camera
	if(glfwGetKey( 'A' ) == GLFW_PRESS)
	{
		mCamera.Strafe(-speed * dt);
	}
	else if(glfwGetKey( 'D' ) == GLFW_PRESS)
	{
		mCamera.Strafe(speed * dt);
	}
	// ########## END CAMERA KEYBOARD MOVEMENT ###########
}

void CSimulationView::DrawLights()
{
    std::vector<CTrafficLight>& lights = mModel->GetTrafficLigths();
}

void CSimulationView::DrawParticipants()
{
    std::list<CParticipant>& participants = mModel->GetParticipants();
    std::list<CParticipant>::iterator parIt;
    if( participants.size() > 0)
    {
        std::vector<wmath::Vec3> parPositions;

        parShader.Bind();
        int projViewMatrix = glGetUniformLocation(parShader.GetID(), "mvpMatrix");

        for(parIt = participants.begin(); parIt != participants.end(); ++parIt)
        {
            if((*parIt).Hidden())
                continue;

            parPositions.push_back((*parIt).GetPosition());
        }

        // put in to vertexbuffer
        parVertexBuffer.SubData(&parPositions[0], sizeof(wmath::Vec3) * parPositions.size()  );

        // draw participants
        wmath::Mat4 projView = mCamera.GetProjection() * mCamera.GetView();
        glUniformMatrix4fv(projViewMatrix, 1, GL_FALSE, (GLfloat*)&projView);

        parVertexBuffer.Bind();
        glEnableVertexAttribArray(0);
        parVertexBuffer.SetAttribPointer(0, 3, GL_FLOAT, sizeof(wmath::Vec3), 0 );

        glPointSize(16);
        glDrawArrays(GL_POINTS, 0, parPositions.size());

        parShader.Unbind();
    }
}

void CSimulationView::Draw()
{
    // clear the buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw scene
    mScene.Draw(&mCamera);

    // draw trafficlights
    DrawLights();

    // draw participants
    DrawParticipants();

    // draw skybox
    mSkybox.Draw();

    // show screen
    glfwSwapBuffers();
}
