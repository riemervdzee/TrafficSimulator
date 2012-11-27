/* 
 * File:   RuneSocketSet.cpp
 * Author: Mark van der Wal
 * 
 * Handles sets of sockets for activity
 * 
 * Created on November 26, 2012, 1:21 PM
 */

#include <algorithm>
#include "RuneSocketSet.h"

namespace RuneSocket
{

    RuneSocketSet::RuneSocketSet()
    {
        FD_ZERO( &m_set );
        FD_ZERO( &m_activityset );
    }

    void RuneSocketSet::AddSocket( const BaseSocket& p_sock )
    {
        // add the socket desc to the set
        FD_SET( p_sock.GetSock(), &m_set );

        // if linux, then record the descriptor into the vector, 
        // and check if it's the largest descriptor.
        #ifndef WIN32
            m_socketdescs.insert( p_sock.GetSock() );
        #endif

    }

    void RuneSocketSet::RemoveSocket( const BaseSocket& p_sock )
    {
        FD_CLR( p_sock.GetSock(), &m_set );

        #ifndef WIN32
            // remove the descriptor from the vector
            m_socketdescs.erase( p_sock.GetSock() );
        #endif

    }

}       // end namespace RuneSocket