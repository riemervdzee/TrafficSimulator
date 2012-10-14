#include "../../Source/TrafficSimulator/CSimulationView.h"
#include "../../Source/TrafficSimulator/CSimulationController.h"
#include "../../Source/TrafficSimulator/CSimulationModel.h"

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
}

void CSimulationView::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    glfwSwapBuffers();
}
