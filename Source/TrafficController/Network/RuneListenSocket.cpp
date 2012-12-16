/*
 * File:   RuneListenSocket.cpp
 * Author: wilds
 *
 * Created on November 26, 2012, 1:54 PM
 */

#include "RuneListenSocket.h"
#include <cstring>

namespace RuneSocket
{
        // ====================================================================
    // Function:    ListeningSocket
    // Purpose:     Constructor. Constructs the socket with initial values
    // ====================================================================
    RuneListenSocket::RuneListenSocket()
    {
        m_listening = false;
    }

    // ====================================================================
    // Function:    Listen
    // Purpose:     this function will tell the socket to listen on a
    //              certain port
    // p_port:      This is the port that the socket will listen on.
    // ====================================================================
    void RuneListenSocket::Listen( port p_port )
    {
        int err;

        // first try to obtain a socket descriptor from the OS, if
        // there isn't already one.
        if( m_sock == -1 )
        {
            m_sock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

            // throw an exception if the socket could not be created
            if( m_sock == -1 )
            {
                throw Exception( GetError() );
            }
        }

        // set the SO_REUSEADDR option on the socket, so that it doesn't
        // hog the port after it closes.
        int reuse = 1;
        err = setsockopt( m_sock, SOL_SOCKET, SO_REUSEADDR,
                          (char*)(&reuse), sizeof( reuse ) );
        if( err != 0 )
        {
            throw Exception( GetError() );
        }

        // set up the socket address structure
        m_localinfo.sin_family = AF_INET;
        m_localinfo.sin_port = htons( p_port );
        m_localinfo.sin_addr.s_addr = htonl( INADDR_ANY );
        memset( &(m_localinfo.sin_zero), 0, 8 );

        // bind the socket
        err = bind( m_sock, (struct sockaddr*)&m_localinfo,
            sizeof(struct sockaddr));
        if( err == -1 )
        {
            throw Exception( GetError() );
        }

        // now listen on the socket. There is a very high chance that this will
        // be successful if it got to this point, but always check for errors
        // anyway. Set the queue to 8; a reasonable number.
        err = listen( m_sock, 8 );
        if( err == -1 )
        {
            throw Exception( GetError() );
        }

        m_listening = true;
    }


    // ====================================================================
    // Function:    Accept
    // Purpose:     This is a blocking function that will accept an
    //              incomming connection and return a data socket with info
    //              about the new connection.
    // ====================================================================
    RuneDataSocket RuneListenSocket::Accept()
    {
        sock s;
        struct sockaddr_in socketaddress;

        // try to accept a connection
        socklen_t size = sizeof(struct sockaddr);
        s = accept( m_sock, (struct sockaddr*)&socketaddress, &size );
        if( s == -1 )
        {
            throw Exception( GetError() );
        }

        // return the newly created socket.
        return RuneDataSocket( s );
    }


    // ====================================================================
    // Function:    Close
    // Purpose:     closes the socket.
    // ====================================================================
    void RuneListenSocket::Close()
    {
        // close the socket
        BaseSocket::Close();

        // invalidate the variables
        m_listening = false;
    }
}       // end namespace RuneSocket
