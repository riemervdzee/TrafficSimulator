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
    // Empty constructor to override interface (private/non-working) constructors
    cConsoleView() {}

    // Print function
    void Print( std::string str);
};

#endif // CLASS_CONSOLEVIEW_H
