#ifndef INTERFACE_CONSOLEOBSERVER_H
#define INTERFACE_CONSOLEOBSERVER_H

#include <string>

/*
 * Interface for Consoles
 */
class iConsoleObserver
{
public:
    // Virtual deconstructor for inheritance
    virtual ~iConsoleObserver() {};

    //
    virtual void Print( std::string str) = 0;
};

#endif // INTERFACE_CONSOLEOBSERVER_H
