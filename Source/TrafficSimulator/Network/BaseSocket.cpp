/* 
 * File:   BaseSocket.cpp
 * Author: wilds
 * 
 * Created on November 26, 2012, 12:45 PM
 */

#include "BaseSocket.h"

namespace RuneSocket
{
   // ====================================================================
    // Function:    Close
    // Purpose:     closes the socket.
    // ====================================================================
    void BaseSocket::Close()
    {

        // WinSock uses "closesocket" instead of "close", since it treats
        // sockets as completely separate objects to files, whereas unix
        // treats files and sockets exactly the same.
    #ifdef WIN32
        closesocket( m_sock );
    #else
        close( m_sock );
    #endif

        // invalidate the socket
        m_sock = -1;
    }

    // ====================================================================
    // Function:    SetBlocking
    // Purpose:     sets whether the socket is blocking or not.
    // ====================================================================
    void BaseSocket::SetBlocking( bool p_blockmode )
    {
        int err;
       
        #ifdef WIN32
            unsigned long mode = !p_blockmode;
            err = ioctlsocket( m_sock, FIONBIO, &mode );
        #else
            // get the flags
            int flags = fcntl( m_sock, F_GETFL, 0 );

            // set or clear the non-blocking flag
            if( p_blockmode == false )
            {
                flags |= O_NONBLOCK;
            }
            else
            {
                flags &= ~O_NONBLOCK;
            }
            err = fcntl( m_sock, F_SETFL, flags );
        #endif

        if( err == -1 )
        {
            throw( Exception( GetError() ) );
        }

        m_isblocking = p_blockmode;
    }


    // ====================================================================
    // Function:    BasicSocket
    // Purpose:     hidden constructor, meant to prevent people from
    //              instantiating this class. You should be using direct
    //              implementations of this class instead, such as 
    //              ListeningSocket and DataSocket.
    // ====================================================================
    BaseSocket::BaseSocket( sock p_socket )
    : m_sock( p_socket )
    {
        if( p_socket != -1 )
        {
            socklen_t s = sizeof(m_localinfo);
            getsockname( p_socket, (sockaddr*)(&m_localinfo), &s );
        }

        // the socket is blocking by default
        m_isblocking = true;
    }
}   // end namespace RuneSocket