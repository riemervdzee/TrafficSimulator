// class cConsoleView

#include <iostream>
#include <conio.h>
#include "cConsoleView.h"
using namespace std;


/*
 * A very difficult print function..
 */
void cConsoleView::Print(const std::string& msg)
{
    std::cout << msg << std::endl;
}

/*
 * Reads for a Q press
 */
bool cConsoleView::GetQuitPress()
{
#ifndef HAS_GETCH
    return false;
#else

    // Try to get a char in the keyboard buffer
    int val = getch();

    // Is it empty?
    if( val == 0)
        return false;

    // Poll for Q
    if(val == 'q' || val == 'Q')
        return true;
    else
        return false;
#endif
}
