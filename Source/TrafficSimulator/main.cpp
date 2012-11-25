#include "CApplication.h"

int main()
{
    CApplication app;

    // create application
    if( !app.Create(1024, 664, false) )
    //if( !app.Create(1366, 768, true) )
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

