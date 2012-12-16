/* 
 * File:   RuneDataSocket.cpp
 * Author: wilds
 * 
 * Created on November 26, 2012, 1:49 PM
 */

#include "RuneDataSocket.h"
#include <cstring>

namespace RuneSocket
{
    // ====================================================================
    // Function:    DataSocket
    // Purpose:     Constructs the data socket with optional values
    // ====================================================================
    RuneDataSocket::RuneDataSocket( sock p_socket )
    : BaseSocket( p_socket ),
    m_connected( false )
    {
        if( p_socket != -1 )
        {
            socklen_t s = sizeof(m_remoteinfo);
            getpeername( p_socket, (sockaddr*)(&m_remoteinfo), &s );
            m_connected = true;
        }
    }


    // ====================================================================
    // Function:    Connect
    // Purpose:     Connects this socket to another socket. This will fail
    //              if the socket is already connected, or the server
    //              rejects the connection.
    // ====================================================================
    void RuneDataSocket::Connect( ipaddress p_addr, port p_port )
    {
        int err;

        // if the socket is already connected...
        if( m_connected == true )
        {
            throw Exception( EAlreadyConnected );
        }

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
        
        // Disable crappy windows Naggle
        int nodelay = 1;
        err = setsockopt( m_sock, SOL_SOCKET, TCP_NODELAY,
                          (char*)(&nodelay), sizeof( nodelay ) );

        if( err != 0 )
        {
            throw Exception( GetError() );
        }

        // set up the socket address structure
        m_remoteinfo.sin_family = AF_INET;
        m_remoteinfo.sin_port = htons( p_port );
        m_remoteinfo.sin_addr.s_addr = p_addr;
        memset( &(m_remoteinfo.sin_zero), 0, 8 );

        // now the socket is created, so connect it.
        socklen_t s = sizeof(struct sockaddr);
        err = connect( m_sock, (struct sockaddr*)(&m_remoteinfo), s );
        if( err == -1 )
        {
            throw Exception( GetError() );
        }

        m_connected = true;

        // to get the local port, you need to do a little more work
        err = getsockname( m_sock, (struct sockaddr*)(&m_localinfo), &s );
        if( err != 0 )
        {
            throw Exception( GetError() );
        }
    }

    // ====================================================================
    // Function:    Send
    // Purpose:     Attempts to send data, and returns the number of
    //              of bytes sent
    // ====================================================================
    int RuneDataSocket::Send( const char* p_buffer, int p_size )
    {
        int err;

        // make sure the socket is connected first.
        if( m_connected == false )
        {
            throw Exception( ENotConnected );
        }

        // attempt to send the data
        err = send( m_sock, p_buffer, p_size, 0 );
        if( err == -1 )
        {
            Error e = GetError();
            if( e != EOperationWouldBlock )
            {
                throw Exception( e );
            }

            // if the socket is nonblocking, we don't want to send a terminal
            // error, so just set the number of bytes sent to 0, assuming
            // that the client will be able to handle that.
            err = 0;
        }

        // return the number of bytes successfully sent
        return err;
    }

    // ====================================================================
    // Function:    Receive
    // Purpose:     Attempts to recieve data from a socket, and returns the
    //              amount of data received.
    // ====================================================================
    int RuneDataSocket::Receive( char* p_buffer, int p_size )
    {
        int err;

        // make sure the socket is connected first.
        if( m_connected == false )
        {
            throw Exception( ENotConnected );
        }

        // attempt to recieve the data
        err = recv( m_sock, p_buffer, p_size, 0 );
        if( err == 0 )
        {
            throw Exception( EConnectionClosed );
        }
        if( err == -1 )
        {
            throw Exception( GetError() );
        }

        // return the number of bytes successfully recieved
        return err;
    }

    // ====================================================================
    // Function:    Close
    // Purpose:     closes the socket.
    // ====================================================================
    void RuneDataSocket::Close()
    {
        if( m_connected == true )
        {
            shutdown( m_sock, 2 );
        }

        // close the socket
        BaseSocket::Close();

        m_connected = false;
    }
    
}       // end namespace RuneSocket