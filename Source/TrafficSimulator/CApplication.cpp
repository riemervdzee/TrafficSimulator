#include "../../Source/TrafficSimulator/CApplication.h"
#include "../../Source/TrafficSimulator/CSimulationController.h"
#include "../../Source/TrafficSimulator/CSimulationModel.h"
#include "../../Source/TrafficSimulator/CSimulationView.h"

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

	// set data members
	mWidth = width;
	mHeight = height;

	// create model and controller
	mModel = new CSimulationModel();
	mController = new CSimulationController(mModel);
	mController->SetRunning(true);

	// add views
	mController->SetSimulationView( new CSimulationView() );

	return true;
}

void CApplication::Destroy()
{
    // Destroy model and controller
    if(mModel)
        delete mModel;

    if(mController)
        delete mController;

    // Terminate glfw
    glfwTerminate();
}

void CApplication::AdvanceFrame()
{
    // Updates
    mModel->UpdateSim();
}

bool CApplication::IsRunning()
{
    return (mController ? mController->GetIsRunning() : false);
}
