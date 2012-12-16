#include <iostream>
#include "cBlockControl.h"
#include "EventQueue/iAction.h"
using namespace std;

/**
 * Constructor
 */
cBlockControl::cBlockControl( iAction* A) : _Blocking( 0)
{
    // First get all wanted information from the iAction object
    TRADEFS::PARTICIPANTS type  = A->getType();
    TRADEFS::DIRECTION fromDir  = A->getFromDirection();
    TRADEFS::DIRECTION toDir    = A->getToDirection();
    int                fromLane = A->getFromLane();

    // We can treat everything the same for except Pedestrians
    if( type == TRADEFS::PEDESTRIAN)
    {
        // With Pedestrians we got two directions
        if( fromLane == 0)
        {
            switch( fromDir)
            {
                case TRADEFS::NORTH:
                    SetBit( 0);
                    SetBit( 1);
                    break;

                case TRADEFS::EAST:
                    SetBit( 2);
                    SetBit( 3);
                    break;

                case TRADEFS::SOUTH:
                    SetBit( 4);
                    SetBit( 5);
                    break;

                case TRADEFS::WEST:
                    SetBit( 6);
                    SetBit( 7);
                    break;
            }
        }
        else
        {
            switch( fromDir)
            {
                case TRADEFS::NORTH:
                    SetBit( 8);
                    SetBit( 9);
                    break;

                case TRADEFS::EAST:
                    SetBit( 10);
                    SetBit( 11);
                    break;

                case TRADEFS::SOUTH:
                    SetBit( 12);
                    SetBit( 13);
                    break;

                case TRADEFS::WEST:
                    SetBit( 14);
                    SetBit( 15);
                    break;
            }
        }
    }
    // For Cars, Busses and Bikes
    else
    {
        // Tells us which posistions we always block when starting at a certain position
        switch( fromDir)
        {
            case TRADEFS::NORTH:
                SetBit( 0);
                SetBit( 8);
                SetBit(16);
                break;

            case TRADEFS::EAST:
                SetBit( 2);
                SetBit( 10);
                SetBit( 17);
                break;

            case TRADEFS::SOUTH:
                SetBit( 4);
                SetBit( 12);
                SetBit( 19);
                break;

            case TRADEFS::WEST:
                SetBit( 6);
                SetBit( 14);
                SetBit( 18);
                break;
        }

        // Tells us which posistions we always block when we are _Ending_ at a certain position
        switch( toDir)
        {
            case TRADEFS::NORTH:
                SetBit( 1);
                SetBit( 9);
                SetBit(17);
                break;

            case TRADEFS::EAST:
                SetBit( 3);
                SetBit( 11);
                SetBit( 19);
                break;

            case TRADEFS::SOUTH:
                SetBit( 5);
                SetBit( 13);
                SetBit( 18);
                break;

            case TRADEFS::WEST:
                SetBit( 7);
                SetBit( 15);
                SetBit( 16);
                break;
        }
    }

    // There are 4 special cases where extra bits need to be set
    if( fromDir == TRADEFS::NORTH && toDir == TRADEFS::EAST ) SetBit( 18);
    if( fromDir == TRADEFS::EAST  && toDir == TRADEFS::SOUTH) SetBit( 16);
    if( fromDir == TRADEFS::SOUTH && toDir == TRADEFS::WEST ) SetBit( 17);
    if( fromDir == TRADEFS::WEST  && toDir == TRADEFS::NORTH) SetBit( 19);

}

