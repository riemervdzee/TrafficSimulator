#include "RuneSocketUtil.h"
#include "RuneSocketError.h"

#include <time.h>
#ifdef WIN32
    #include "windows.h"
#else
    #include <sys/time.h>
#endif

// this is a simple object-oriented socket library wrapper around
// winsock/BSDsockets. It will only use TCP/IP as it's method of communication,
// and will have no UDP support at all.
namespace RuneSocket
{
    // ========================================================================
    //  This class is designed to be a global singleton that initializes
    //  and shuts down Winsock.
    // ========================================================================
    #ifdef WIN32                // windows 95 and above
        class System
        {
        public:
            // ================================================================
            //  This initializes winsock
            // ================================================================
            System()
            {
                // attempt to start up the winsock lib
                WSAStartup( MAKEWORD( 2, 2 ), &m_WSAData );
            }

            // ========================================================================
            //  This shuts down winsock
            // ========================================================================
            ~System()
            {
                // attempt to close down the winsock lib
                WSACleanup();
            }

        protected:
            // holds information about winsock
            WSADATA m_WSAData;
        };

        System gSystem; // Automaticly initializes if in windows
    #endif

    // ============================================================
    // This is a hidden class, designed to initialize the win32
    // performance counter frequency value.
    // ============================================================
    #ifdef WIN32
        class Win32PerformanceCounter
        {
        public:
            Win32PerformanceCounter()
            {
                // get the "ticks per second" value
                QueryPerformanceFrequency( (LARGE_INTEGER*)(&m_frequency) );

                // convert it into a "ticks per millisecond" value
                m_frequency = m_frequency / 1000;
            }

            // this is the frequency of the performance counter, in 
            // "ticks per millisecond"
            sint64 m_frequency;
        };

        Win32PerformanceCounter g_win32counter;
    #endif

    // ============================================================
    // These functions get a time value. The Actual meaning of this 
    // time is undefined; it is only meant to be relative.
    // ============================================================
    sint64 GetTimeMS()
    {
        #ifdef WIN32
            sint64 t;
            QueryPerformanceCounter( (LARGE_INTEGER*)(&t) );
            return t / g_win32counter.m_frequency;
        #else
            struct timeval t;
            sint64 s;
            
            // get the time of day
            gettimeofday( &t, 0 );

            // calculate the number of milliseconds represented by the seconds
            s = t.tv_sec;
            s *= 1000;

            // calculate the milliseconds now
            s += (t.tv_usec / 1000);

            // return the value
            return s;
        #endif
    }


    sint64 GetTimeS()
    {
        return GetTimeMS() / 1000;
    }

    sint64 GetTimeM()
    {
        return GetTimeMS() / 60000;
    }

    sint64 GetTimeH()
    {
        return GetTimeMS() / 3600000;
    }
    

    // ============================================================
    // This prints a timestamp in 24 hours hh:mm:ss format
    // ============================================================
    std::string TimeStamp()
    {
        char str[9];

        // get the time, and convert it to struct tm format
        time_t a = time(0);
        struct tm* b = localtime( &a );

        // print the time to the string
        strftime( str, 9, "%H:%M:%S", b );

        return str;
    }


    // ============================================================
    // This prints a datestamp in YYYY:MM:DD format
    // ============================================================
    std::string DateStamp()
    {
        char str[11];

        // get the time, and convert it to struct tm format
        time_t a = time(0);
        struct tm* b = localtime( &a );

        // print the time to the string
        strftime( str, 11, "%Y.%m.%d", b );

        return str;
    }


    Timer::Timer()
    {
        m_starttime = 0;
        m_inittime = 0;
    }


    void Timer::Reset( sint64 p_timepassed )
    {
        m_starttime = p_timepassed;
        m_inittime = GetTimeMS();
    }

    sint64 Timer::GetMS()
    {
        // return the amount of time that has elapsed since the timer
        // was initialized, plus whatever starting time the timer was given.
        return (GetTimeMS() - m_inittime) + m_starttime;
    }

    sint64 Timer::GetS()
    {
        return GetMS() / 1000;
    }

    sint64 Timer::GetM()
    {
        return GetMS() / 60000;
    }

    sint64 Timer::GetH()
    {
        return GetMS() / 3600000;
    }

    sint64 Timer::GetD()
    {
        return GetMS() / 86400000;
    }
    
    sint64 Timer::GetY()
    {
        return GetD() / 365;
    }

    // ========================================================================
    // Function:    GetIPAddress
    // Purpose:     To get the IP address of the string as an ipaddress
    //              structure. Throws an exception if the address cannot be
    //              converted.
    // ========================================================================
    ipaddress GetIPAddress( const std::string p_address )
    {
        
        if( IsIPAddress( p_address ) )
        {
            // if the address is just a regular IP address, there's no need
            // to do a DNS lookup, so just convert the string directly into
            // its binary format.
            ipaddress addr = inet_addr( p_address.c_str() );
            
            // if the address is invalid, throw a HOST_NOT_FOUND exception.
            if( addr == INADDR_NONE )
            {
                throw Exception( EDNSNotFound );
            }

            // by this point, the address is valid, so return it.
            return addr;
        }
        else
        {
            // the address isn't an IP address, so we need to look it up using
            // DNS. 
            struct hostent* host = gethostbyname( p_address.c_str() );

            // if there was an error, throw an exception.
            if( host == 0 )
            {
                // get the error from h_errno.
                throw Exception( GetError( false ) );
            }

            // now perform some really wierd casting tricks to get the value.
            // h_addr is a char*, so cast it into an ipaddress*, and 
            // dereference it to get the value.
            return *((ipaddress*)host->h_addr);
        }
    }


    // ========================================================================
    // Function:    GetIPString
    // Purpose:     Converts an ipaddress structure to a string in numerical
    //              format.
    // ========================================================================
    std::string GetIPString( ipaddress p_address )
    {
        // return a new string containing the address.
        // (god that is some ugly casting going on... stupid language)
        char* str = inet_ntoa( *((in_addr*)&p_address) );
        if( str == 0 )
        {
            return std::string( "Invalid IP Address" );
        }
        return std::string( str );
    }

    // ========================================================================
    // Function:    GetHostNameString
    // Purpose:     Converts an ipaddress structure to a string using
    //              reverse-DNS lookup. This may block.
    // ========================================================================
    std::string GetHostNameString( ipaddress p_address )
    {
        // get the host info.
        struct hostent* host = gethostbyaddr( (char*)&p_address, 4, AF_INET );

        // if there was an error, throw an exception.
        if( host == 0 )
        {
            // get the error from h_errno.
            throw Exception( GetError( false ) );
        }

        return std::string( host->h_name );
    }

    // ========================================================================
    // Function:    IsIPAddress
    // Purpose:     determines if a string contains a pure numerical IP address
    //              (returns true) or a DNS'able address (returns false)
    // ========================================================================
    bool IsIPAddress( const std::string p_address )
    {
        // scan through the string to see if it's a pure IP address or not.
        // basically, we assume that any string with characters other than
        // numerics and periods needs to be DNS'ed.
        for( size_t i = 0; i < p_address.length(); i++ )
        {
            if( ( p_address[i] < '0' || p_address[i] > '9' ) && 
                p_address[i] != '.' )
                return false;
        }
        return true;
    }

}   // end namespace RuneSocket