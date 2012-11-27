/* 
 * File:   RuneSocketUtil.h
 * Author: Mark van der Wal
 *
 * RuneSocket library utility functions
 * 
 * Created on November 26, 2012, 1:01 PM
 */

#ifndef RUNESOCKETUTIL_H
#define	RUNESOCKETUTIL_H

// ========================================================================
//  Include Files
// ========================================================================
#include <string>
#include "RuneSocketDefs.h"

namespace RuneSocket
{
    // ============================================================
    // These functions get a time value. The Actual meaning of this 
    // time is undefined; it is only meant to be relative.
    // ============================================================
    sint64 GetTimeMS();
    sint64 GetTimeS();
    sint64 GetTimeM();
    sint64 GetTimeH();


    // ============================================================
    // This prints a timestamp in 24 hours hh:mm:ss format
    // ============================================================
    std::string TimeStamp();


    // ============================================================
    // This prints a datestamp in YYYY:MM:DD format
    // ============================================================
    std::string DateStamp();
    

    // ============================================================
    //  The Timer Class
    // ============================================================
    class Timer
    {
    public:
        
        Timer();
        
        void Reset( sint64 p_timepassed = 0 );
        
        sint64 GetMS();
        sint64 GetS();
        sint64 GetM();
        sint64 GetH();
        sint64 GetD();
        sint64 GetY();

    protected:

        // this is the system time at which the timer was initialized
        sint64 m_inittime;

        // this is the official "starting time" of the timer.
        sint64 m_starttime;
    };


    inline sint64 seconds( sint64 t )   { return t * 1000; }
    inline sint64 minutes( sint64 t )   { return t * 60 * 1000; }
    inline sint64 hours( sint64 t )     { return t * 60 * 60 * 1000; }
    inline sint64 days( sint64 t )      { return t * 24 * 60 * 60 * 1000; }
    inline sint64 weeks( sint64 t )     { return t * 7 * 24 * 60 * 60 * 1000; }
    inline sint64 years( sint64 t )     { return t * 365 * 24 * 60 * 60 * 1000; }

    // ========================================================================
    // Function:    GetIPAddress
    // Purpose:     To get the IP address of the string as an ipaddress
    //              structure. Throws an exception if the address cannot be
    //              converted.
    // ========================================================================
    ipaddress GetIPAddress( const std::string p_address );

    // ========================================================================
    // Function:    GetIPString
    // Purpose:     Converts an ipaddress structure to a string in numerical
    //              format.
    // ========================================================================
    std::string GetIPString( ipaddress p_address );

    // ========================================================================
    // Function:    GetHostNameString
    // Purpose:     Converts an ipaddress structure to a string using
    //              reverse-DNS lookup. This may block.
    // ========================================================================
    std::string GetHostNameString( ipaddress p_address );

    // ========================================================================
    // Function:    IsIPAddress
    // Purpose:     determines if a string contains a pure numerical IP address
    //              (returns true) or a DNS'able address (returns false)
    // ========================================================================
    bool IsIPAddress( const std::string p_address );

}   // end namespace RuneSocket

#endif	/* RUNESOCKETUTIL_H */