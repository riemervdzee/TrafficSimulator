#include <GL/glfw.h>

const unsigned int gWindowWidth = 1024;
const unsigned int gWindowHeight = 768;

int main()
{
	int running = 1;

	// init glfw
	if( !glfwInit() )
	{
		// could not init glfw
		return 0;
	}

	// create a window
	if( glfwOpenWindow(gWindowWidth, gWindowHeight, 8, 8, 8, 8, 24, 8, GLFW_WINDOW) == GL_FALSE)
	{
        // terminate glfw
        glfwTerminate();
        return 0;
	}

	// set window styles
	glfwSetWindowTitle("TrafficSimulator 2012/2013");

	// init OpenGL
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	// main loop
	while( running )
	{
		if( glfwGetKey( GLFW_KEY_ESC ) == GLFW_PRESS )
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
	return 0;
}
