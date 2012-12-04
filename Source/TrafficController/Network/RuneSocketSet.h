/*
 * File:   RuneSocketSet.h
 * Author: Mark van der Wal
 *
 * Handles sets of sockets for activity
 *
 * Created on November 26, 2012, 1:21 PM
 */

#ifndef RUNESOCKETSET_H
#define	RUNESOCKETSET_H

#include "RuneSocketDefs.h"
#include "BaseSocket.h"
#include <set>

namespace RuneSocket
{
    const int MAX = FD_SETSIZE;

    enum FD_ACTION
    {
        READ = 0,
        WRITE,
        EXCEP
    };

    class RuneSocketSet
    {
    public:
        RuneSocketSet();

        void AddSocket( const BaseSocket& p_sock );
        void RemoveSocket( const BaseSocket& p_sock );

        inline int Poll( long p_time = 0 )
        {
            // this is the time value structure. It will determine how long
            // the select function will wait.
            struct timeval t = { 0, p_time * 1000 };

            // copy the set over into the activity set.
            m_readset = m_set;
            m_writeset = m_set;
            m_excepset = m_set;

            // now run select() on the sockets.
            #ifdef WIN32
                return select( 0, &m_readset, &m_writeset, &m_excepset, &t );
            #else
                if( m_socketdescs.size() == 0 ) return 0;
                return select( *(m_socketdescs.rbegin()) + 1, &m_readset, &m_writeset, &m_excepset, &t );
            #endif
        }

        inline bool HasActivity( const BaseSocket& p_sock, FD_ACTION action )
        {
            switch(action)
            {
                case READ:
                    return FD_ISSET( p_sock.GetSock(), &m_readset ) != 0;
                case WRITE:
                    return FD_ISSET( p_sock.GetSock(), &m_writeset ) != 0;
                case EXCEP:
                    return FD_ISSET( p_sock.GetSock(), &m_excepset ) != 0;
                default:
                    return false;
            }
        }


    protected:

        // a set representing the socket descriptors.
        fd_set m_set;

        // this set will represent all the sockets that have activity on them.
        fd_set m_readset;
        fd_set m_writeset;
        fd_set m_excepset;

        // this is only used for linux, since select() requires the largest
        // descriptor +1 passed into it. BLAH!
        #ifndef WIN32
            std::set<sock> m_socketdescs;
        #endif
    };

}       // end namespace RuneSocket

#endif	/* RUNESOCKETSET_H */

