/* 
 * File:   RuneSocketDefs.h
 * Author: Mark van der Wal
 *
 * Contains al definitions for the socket library
 * 
 * Created on November 26, 2012, 12:54 PM
 */

#ifndef RUNESOCKETDEFS_H
#define	RUNESOCKETDEFS_H

#include <iostream>
#include <fstream>
#include <string>

// ========================================================================
//  Include Files
// ========================================================================
#ifdef WIN32                // windows 95 and above
    #include "winsock2.h"       // almost everything is contained in one file.
    #include "Ws2tcpip.h"

    #ifndef socklen_t
        typedef int socklen_t;
    #endif

#else                       // UNIX/Linux
    #include <sys/types.h>      // header containing all basic data types and
                                // typedefs
    #include <sys/socket.h>     // header containing socket data types and
                                // functions
    #include <netinet/in.h>     // IPv4 and IPv6 stuff
    #include <unistd.h>         // for gethostname()
    #include <netdb.h>          // for DNS - gethostbyname()
    #include <arpa/inet.h>      // contains all inet_* functions
    #include <errno.h>          // contains the error functions
    #include <fcntl.h>          // file control
#endif

namespace RuneSocket
{

    #ifdef WIN32
        #if _MSC_VER >= 1300
            #define GOODCOMPILER
        #else
            #define CRAPPYCOMPILER
        #endif
    #endif

    #ifdef __GNUC__
        #define GOODCOMPILER
    #endif


    // ============================================================
    //  This defines the 64 bit datatype
    // ============================================================

    // ------------------------------
    //  LINUX
    // ------------------------------
    #ifdef __GNUC__
        typedef long long int sint64;
        typedef unsigned long long int uint64;
    #endif


    // ------------------------------
    //  Visual C++
    // ------------------------------
    #ifdef WIN32
        typedef __int64 sint64;
        typedef unsigned __int64 uint64;
    #endif


    typedef signed long int sint32;
    typedef unsigned long int uint32;
    typedef signed short int sint16;
    typedef unsigned short int uint16;
    typedef signed char sint8;
    typedef unsigned char uint8;

    // ========================================================================
    //  Globals and Typedefs
    // ========================================================================
    #ifdef WIN32                // windows 95 and above

        typedef SOCKET sock;        // Although sockets are int's on unix, 
                                    // windows uses it's own typedef of
                                    // SOCKET to represent them. If you look
                                    // in the Winsock2 source code, you'll see
                                    // that it is just a typedef for int, but
                                    // there is absolutely no garuntee that it
                                    // won't change in a later version.
                                    // therefore, in order to avoid confusion,
                                    // this library will create it's own basic
                                    // socket descriptor typedef


    #else                       // UNIX/Linux
        typedef int sock;           // see the description above.

    #endif

    // ========================================================================
    //  Ports will be in host byte order, but IP addresses in network byte 
    //  order. It's easier this way; ports are usually accessed as numbers,
    //  but IP addresses are better accessed through the string functions.
    // ========================================================================
    typedef unsigned short int port;        // define the port type.
    typedef unsigned long int ipaddress;    // an IP address for IPv4


}   // end namespace RuneSocket

#endif	/* RUNESOCKETDEFS_H */

