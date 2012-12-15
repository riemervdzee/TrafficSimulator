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

    // Prints a string to console
    virtual void Print(const std::string& msg) = 0;

    // Check if we got orders to quit the server
    virtual bool GetQuitPress() = 0;
};

#endif // INTERFACE_CONSOLEOBSERVER_H
