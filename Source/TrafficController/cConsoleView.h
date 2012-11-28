#ifndef CLASS_CONSOLEVIEW_H
#define CLASS_CONSOLEVIEW_H

#include "iAbstractView.h"
#include "iConsoleObserver.h"

/*
 *
 */
class cConsoleView : public iAbstractView, public iConsoleObserver
{
public:
    //
    ~cConsoleView() {}

    // Print function
    void Print( std::string str);

    // Reads keyboard input for the Q key
    bool GetQuitPress();
};

#endif // CLASS_CONSOLEVIEW_H
