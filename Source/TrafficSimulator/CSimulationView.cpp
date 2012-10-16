#include "CSimulationView.h"
#include "CSimulationController.h"
#include "CSimulationModel.h"

#include <GL/glfw.h>
#include <cmath>

CSimulationView::CSimulationView(int width, int height)
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);

/*
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat zNear = 0.1f;
    GLfloat zFar = 255.0f;
    GLfloat aspect = float(width)/float(height);
    GLfloat fH = tan( float(70.0f / 360.0f * 3.14159f) ) * zNear;
    GLfloat fW = fH * aspect;
    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
    glPushMatrix();*/

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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
}

void CSimulationView::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 2.0f, 1.0f);
    glRotatef(10.0f, 1.0f, 0.0f, 0.0f);

    glBegin(GL_TRIANGLES);
        //glColor3f(0.1f, 0.8f, 0.1f);
        glVertex3f(-1.0f, -1.0f, 0.0);
        glVertex3f(1.0, -1.0f,  0.0);
        glVertex3f(0.0, 1.0f, 0.0f);
    glEnd();

    glfwSwapBuffers();
}
