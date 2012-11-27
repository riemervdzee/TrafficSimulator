/* 
 * File:   RuneSocketError.h
 * Author: Mark van der Wal
 * 
 * Socket error handling
 *
 * Created on November 26, 2012, 1:06 PM
 */

#ifndef RUNESOCKETERROR_H
#define	RUNESOCKETERROR_H

// ========================================================================
//  Include Files
// ========================================================================
#include "RuneSocketDefs.h"
#include <exception>
#include <string>

namespace RuneSocket
{
    // ========================================================================
    // Description: Error codes for the socket library.
    // ========================================================================
    enum Error
    {
        // errors that shouldn't happen, so if they do, something is wrong:
        ESeriousError,
        
        // these errors are common
        ENetworkDown,
        ENoSocketsAvailable,
        ENoMemory,
        EAddressNotAvailable,
        EAlreadyConnected,
        ENotConnected,
        EConnectionRefused,
        ENetworkUnreachable,
        ENetworkReset,
        EHostUnreachable,
        EHostDown,
        EConnectionAborted,
        EConnectionReset,
        EOperationWouldBlock,

        // DNS errors
        EDNSNotFound,
        EDNSError,
        ENoDNSData,

        // These errors are specific errors that should never or rarely occur.
        EInProgress,
        EInterrupted,
        EAccessDenied,
        EInvalidParameter,
        EAddressFamilyNotSupported,
        EProtocolFamilyNotSupported,
        EProtocolNotSupported,
        EProtocolNotSupportedBySocket,
        EOperationNotSupported,
        EInvalidSocketType,
        EInvalidSocket,
        EAddressRequired,
        EMessageTooLong,
        EBadProtocolOption,
        EAddressInUse,
        ETimedOut,
        EShutDown,


        // auxilliary socketlib errors
        ESocketLimitReached,
        ENotAvailable,
        EConnectionClosed
    };


    // ========================================================================
    // Description: This translates error codes from the native platoform
    //              format into the SocketLib format
    // ========================================================================
    Error TranslateError( int p_error, bool p_errno );

    // ========================================================================
    // Description: This function acts as a simple wrapper for retrieving
    //              socket library errors from errno or h_errno.
    // ========================================================================
    Error GetError( bool p_errno = true );

    // ========================================================================
    // Type:        Exception
    // Purpose:     A generic socket exception class that holds an error, and
    //              an optional text string describing the error in more detail
    // ========================================================================
    class Exception : public std::exception
    {
    public:
        // ====================================================================
        // Function:    Exception
        // Purpose:     To initialize the socket exception with a specific
        //              error code.
        // ====================================================================
        Exception( Error p_code );

        // ====================================================================
        // Function:    Error
        // Purpose:     To retrieve the error code of the socket.
        // ====================================================================
        Error ErrorCode();

        // ====================================================================
        // Function:    PrintError
        // Purpose:     Print the error message to a string
        // ====================================================================
        std::string PrintError();


    protected:
        Error m_code;
    };

} // end namespace RuneSocket

#endif	/* RUNESOCKETERROR_H */