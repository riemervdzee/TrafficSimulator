/* 
 * File:   RuneDataSocket.h
 * Author: Mark van der Wal
 *
 * TCP data socket
 * 
 * Created on November 26, 2012, 1:49 PM
 */

#ifndef RUNEDATASOCKET_H
#define	RUNEDATASOCKET_H

#include "BaseSocket.h"

namespace RuneSocket
{
    // ========================================================================
    // Class:       DataSocket
    // Purpose:     A variation of the BasicSocket base class that handles
    //              TCP/IP data connections.
    // ========================================================================
    class RuneDataSocket : public BaseSocket
    {
    public:
        // ====================================================================
        // Function:    DataSocket
        // Purpose:     Constructs the data socket with optional values
        // ====================================================================
        RuneDataSocket( sock p_socket = -1 );

        // ====================================================================
        // Function:    GetRemoteAddress
        // Purpose:     get the IP address of the remote host.
        // ====================================================================
        inline ipaddress GetRemoteAddress() const
        {
            return m_remoteinfo.sin_addr.s_addr;
        }

        // ====================================================================
        // Function:    GetRemotePort
        // Purpose:     gets the remote port of the socket
        // ====================================================================
        inline port GetRemotePort() const
        {
            return ntohs( m_remoteinfo.sin_port );
        }

        // ====================================================================
        // Function:    IsConnected
        // Purpose:     Determines if the socket is connected or not.
        // ====================================================================
        inline bool IsConnected() const
        {
            return m_connected;
        }

        // ====================================================================
        // Function:    Connect
        // Purpose:     Connects this socket to another socket. This will fail
        //              if the socket is already connected, or the server
        //              rejects the connection.
        // ====================================================================
        void Connect( ipaddress p_addr, port p_port );

        // ====================================================================
        // Function:    Send
        // Purpose:     Attempts to send data, and returns the number of
        //              of bytes sent
        // ====================================================================
        int Send( const char* p_buffer, int p_size );

        // ====================================================================
        // Function:    Receive
        // Purpose:     Attempts to receive data from a socket, and returns the
        //              amount of data received.
        // ====================================================================
        int Receive( char* p_buffer, int p_size );

        // ====================================================================
        // Function:    Close
        // Purpose:     closes the socket.
        // ====================================================================
        void Close();

    protected:

        bool m_connected;               // is the socket connected?

        sockaddr_in m_remoteinfo;// structure containing information
        // about the remote connection

    };
}       // end namespace RuneSocket

#endif	/* RUNEDATASOCKET_H */