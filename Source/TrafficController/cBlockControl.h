#ifndef CLASS_BLOCKCONTROL_H
#define CLASS_BLOCKCONTROL_H

#include "EventQueue/iAction.h"

/*
 * Our epic asci drawing of our blocking checking lanes (LEFT the position, RIGHT the numerical value of that position)
 * We got four main areas on the crossroad itself, and 16 for pedestrians
 * Although pedestrians are cut off at the middle, they require the whole line.
 * But this cut off is needed for better solutions of this algorithm
 * Also pedestrians can walk both sides, without blocking eachother and that is why we need it in both directions.. sucky heh?
 *
 * Note that every number stands for a binary position. When assembled, comparing and adding is easy
 *
 *       ---> --->                      0     1
 *       <--- <---                      8     9
 *   ^ |           ^ |         7  15              10   2
 *   | V  []   []  | V                 16    17
 *
 *   ^ |  []   []  ^ |                 18    19
 *   | V           | V         6  14              11   3
 *       ---> --->                     13    12
 *       <--- <---                      5     4
 *
 */
class cBlockControl
{
protected:
    // Tells which points we are blocking already
    int _Blocking;

    // Set a specific bit
    inline void SetBit( int bit) { _Blocking |= 1 << bit;}

public:
    // Empty constructor
    cBlockControl() : _Blocking(0)  {}

    // Base a Blocking value upon an iAction
    cBlockControl( iAction* A);

    // Compares a BC with this, returns true when they don't block
    inline bool Compare( const cBlockControl& BC) { return (BC._Blocking & _Blocking) == 0;}

    // Adds a BC to the current BC
    inline void Add( const cBlockControl& BC) { _Blocking |= BC._Blocking;}
};

#endif // CLASS_BLOCKCONTROL_H
