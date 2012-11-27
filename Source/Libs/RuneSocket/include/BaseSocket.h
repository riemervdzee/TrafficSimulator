/* 
 * File:   BaseSocket.h
 * Author: Mark van der Wal
 *
 * Created on November 26, 2012, 12:45 PM
 */

#ifndef BASESOCKET_H
#define	BASESOCKET_H

#include "RuneSocketDefs.h"
#include "RuneSocketError.h"

namespace RuneSocket
{
    // ========================================================================
    // Class:       Socket
    // Purpose:     A very basic socket base class that will give the user
    //              the ability to get port and IP information, but not much
    //              else. 
    // ========================================================================
    class BaseSocket 
    {
    public:
        // ====================================================================
        // Function:    GetSock
        // Purpose:     this function returns the internal API socket 
        //              representation. Used by classes and functions that need
        //              to interface directly with the BSD Sockets or Winsock
        //              libraries.
        // ====================================================================
        inline sock GetSock() const
        {
            return m_sock;
        }


        // ====================================================================
        // Function:    GetLocalPort
        // Purpose:     gets the local port of the socket
        // ====================================================================
        inline port GetLocalPort() const
        {
            return ntohs( m_localinfo.sin_port );
        }

        // ====================================================================
        // Function:    GetLocalAddress
        // Purpose:     gets the local address of the socket
        // ====================================================================
        inline ipaddress GetLocalAddress() const
        {
            return m_localinfo.sin_addr.s_addr;
        }

        // ====================================================================
        // Function:    Close
        // Purpose:     closes the socket.
        // ====================================================================
        void Close();

        // ====================================================================
        // Function:    SetBlocking
        // Purpose:     sets whether the socket is blocking or not.
        // ====================================================================
        void SetBlocking( bool p_blockmode );

    protected:
        // ====================================================================
        // Function:    Socket
        // Purpose:     hidden constructor, meant to prevent people from
        //              instantiating this class. You should be using direct
        //              implementations of this class instead, such as 
        //              ListeningSocket and DataSocket.
        // ====================================================================
        BaseSocket( sock p_socket = -1 );


        sock m_sock;                    // this is the underlying representation
                                        // of the actual socket.

        sockaddr_in m_localinfo; // structure containing information
                                        // about the local connection

        bool m_isblocking;              // this tells whether the socket is
                                        // blocking or not.

    };

}   // end namespace RuneSocket

#endif	/* BASESOCKET_H */

