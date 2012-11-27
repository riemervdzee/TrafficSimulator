/* 
 * File:   RuneListenSocket.h
 * Author: wilds
 *
 * Created on November 26, 2012, 1:54 PM
 */

#ifndef RUNELISTENSOCKET_H
#define	RUNELISTENSOCKET_H

#include "BaseSocket.h"
#include "RuneDataSocket.h"

namespace RuneSocket
{
    // ========================================================================
    // Class:       ListeningSocket
    // Purpose:     A variation of the BasicSocket base class that handles
    //              incomming TCP/IP connection requests.
    // ========================================================================
    class RuneListenSocket : public BaseSocket
    {
    public:

        // ====================================================================
        // Function:    ListeningSocket
        // Purpose:     Constructor. Constructs the socket with initial values
        // ====================================================================
        RuneListenSocket();

        // ====================================================================
        // Function:    Listen
        // Purpose:     this function will tell the socket to listen on a 
        //              certain port 
        // p_port:      This is the port that the socket will listen on.
        // ====================================================================
        void Listen( port p_port );

        // ====================================================================
        // Function:    Accept
        // Purpose:     This is a blocking function that will accept an 
        //              incomming connection and return a data socket with info
        //              about the new connection.
        // ====================================================================
        RuneDataSocket Accept();

        // ====================================================================
        // Function:    IsListening
        // Purpose:     Determines if the socket is listening or not.
        // ====================================================================
        inline bool IsListening() const
        {
            return m_listening;
        }

        // ====================================================================
        // Function:    Close
        // Purpose:     closes the socket.
        // ====================================================================
        void Close();

    protected:
        bool m_listening;               // is the socket listening?

    };
}       // end namespace RuneSocket

#endif	/* RUNELISTENSOCKET_H */

