#include "CApplication.h"
#include "CSimulationController.h"
#include "CSimulationModel.h"
#include "CSimulationView.h"
#include "CNetworkView.h"
#include <cstdio>

bool CApplication::Create(unsigned width, unsigned height)
{
	// init glfw
	if( !glfwInit() )
	{
		// could not init glfw
		return false;
	}

    // create a window
	if( glfwOpenWindow(width, height, 8, 8, 8, 8, 24, 8, GLFW_WINDOW) == GL_FALSE)
	{
        // terminate glfw
        glfwTerminate();
        return false;
	}

    // set window stuff
	glfwSetWindowTitle("TrafficSimulator 2012/2013 - Riemer v/d Zee & Mark van der Wal");

	std::cout << "GLFW window created @ " << width << "x" << height << std::endl;

	// init GLEW
	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		printf("Could not initialize GLEW\n");
		return false;
	}

	// set data members
	mWidth = width;
	mHeight = height;

	// create model and controller
	mModel = new CSimulationModel();
	mController = new CSimulationController(mModel);
	mController->SetRunning(true);

	std::cout << "Model created!\nController created!\n\n";

	// add views
	mController->SetSimulationView( new CSimulationView(width, height) );
	mController->SetNetworkView( new CNetworkView() );

	std::cout << "\nAdded a simulation view!\n";
	std::cout << "Added a network view!\n";

	return true;
}

void CApplication::Destroy()
{
    // Destroy model and controller
    if(mModel)
    {
        delete mModel;
        mModel = 0;
    }

    if(mController)
    {
       delete mController;
       mController = 0;
    }

    // Terminate glfw
    glfwTerminate();
}

void CApplication::AdvanceFrame()
{
    glfwPollEvents();

    // Updates
    mModel->UpdateSim();
}

bool CApplication::IsRunning()
{
    return (mController ? mController->GetIsRunning() : false);
}
