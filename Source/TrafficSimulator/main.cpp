#include <GL/glfw.h>
#include <stdlib.h>

const unsigned int gWindowWidth = 1024;
const unsigned int gWindowHeight = 768;

int main()
{
	int running = 1;

	// init glfw
	if( !glfwInit() )
	{
		// could not init glfw
		exit( EXIT_FAILURE );
	}

	// create a window
	if( glfwOpenWindow(gWindowWidth, gWindowHeight, 8, 8, 8, 8, 24, 8, GLFW_WINDOW) == GL_FALSE)
	{
		// could not open window!
		exit( EXIT_FAILURE );
	}

	// init OpenGL
	glClearColor(1.0f, 0, 0, 1.0f);

	// main loop
	while( running )
	{
		// update
		if( !glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED) )
		{
			running = 0;
		}


		// draw
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers();
	}

	// terminate glfw
	glfwTerminate();

	// exit the app
	exit( EXIT_SUCCESS );
}