#ifndef CLASS_CONSOLEVIEW_H
#define CLASS_CONSOLEVIEW_H

#include "iAbstractView.h"
#include "iConsoleObserver.h"
#include <string>

/*
 *
 */
class cConsoleView : public iAbstractView, public iConsoleObserver
{
public:
    //
    ~cConsoleView() {}

    // Print function
    void Print(const std::string& msg);

    // Reads keyboard input for the Q key
    bool GetQuitPress();
};

#endif // CLASS_CONSOLEVIEW_H
