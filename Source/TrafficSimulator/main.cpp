#include "CApplication.h"

int main()
{
    CApplication app;

    // create application
    if( !app.Create(1024, 768) )
        return false;

	// main loop
	while( app.IsRunning() )
	{
        app.AdvanceFrame();
	}

    app.Destroy();

	// exit the app
	return 0;
}

