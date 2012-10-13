#include "CApplication.h"

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

    // set window styles
	glfwSetWindowTitle("TrafficSimulator 2012/2013 - Riemer v/d Zee & Mark van der Wal");

	// set data members
	mWidth = width;
	mHeight = height;
	mIsRunning = true;

	// init subsystems
	InitGraphics();

	return true;
}

void CApplication::InitGraphics()
{
	// init OpenGL
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void CApplication::Destroy()
{
    glfwTerminate();
}

void CApplication::AdvanceFrame()
{
    if( glfwGetKey( GLFW_KEY_ESC ) == GLFW_PRESS )
    {
        mIsRunning = false;
    }

    // draw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwSwapBuffers();
}

void CApplication::LoadInputFile(const char* fileName)
{
    std::ifstream file;
    std::string fileData;
    file.open(fileName);

    if(!file.is_open())
    {
        std::cout << "Can't open the specified file\n";
        return;
    }

    // read in string
    std::string line;
    while( !file.eof() )
    {
        getline( file, line);
        fileData += line + "\n";
    }

    file.close();

    /* JSON CODE
    // ###### JSON ########
    Json::Value root;   // will contains the root value after parsing.
    Json::Reader reader;
    bool parsingSuccessful = reader.parse( fileData, root );
    if ( !parsingSuccessful )
    {
        // report to the user the failure and their locations in the document.
        std::cout  << "Failed to parse configuration\n"
                   << reader.getFormattedErrorMessages();
        return;
    }

    for(unsigned int i = 0; i < root.size(); ++i)
    {
        const Json::Value &element = root[i];
        std::cout << element["time"].asInt() << std::endl;
        std::cout << element["type"].asString() << std::endl;
        std::cout << element["from"].asString() << std::endl;
        std::cout << element["to"].asString() << std::endl;
    }
    */
}
