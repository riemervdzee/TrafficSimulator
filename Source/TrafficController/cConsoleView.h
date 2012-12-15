#ifndef CLASS_CONSOLEVIEW_H
#define CLASS_CONSOLEVIEW_H

#include "iAbstractView.h"
#include "iConsoleObserver.h"
#include <string>

/*
 * Our cConsole view, a class which handles output/input in a nice black screen!
 */
class cConsoleView : public iAbstractView, public iConsoleObserver
{
public:
    // Deconstructor
    ~cConsoleView() {}

    // Print function
    void Print(const std::string& msg);

    // Check if we got orders to quit the server
    bool GetQuitPress();
};

#endif // CLASS_CONSOLEVIEW_H
