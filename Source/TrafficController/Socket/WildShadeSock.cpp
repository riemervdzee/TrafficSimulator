#include "WildShadeSock.hpp"

WSADATA wsaData;

// Creates a TCP socket and bind it and set it to listen on the given port
SOCKET CreateTCPListeningSock(u_short port)
{
	// function fields
	sockaddr_in sockAddr; // the TCP/IP address structure
	ZeroMemory(&sockAddr, sizeof(sockAddr));

	// create TCP socket
	SOCKET tSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	// error checking
	if(tSocket == -1)
	{
		return -1;
	}

	// initialize the address structure
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons( port );
	sockAddr.sin_addr.S_un.S_addr = htonl( INADDR_ANY );

	// bind the socket to the adress, if it fails we destroy the socket
	if ( bind( tSocket, (sockaddr*)&sockAddr, sizeof(sockAddr) ) == -1)
	{
		shutdown(tSocket, 2);
		CloseSocket(tSocket);
		return -1;
	}

	// listen to incoming noises
	if( listen(tSocket, 10) == -1)
	{
		shutdown(tSocket, 2);
		CloseSocket(tSocket);
		return -1;
	}

	return tSocket;
}

// Creates a TCP data socket
// port: the port we will connect to
// ip: the ip address we will connect to
// sockAddr: the address that will hold the server ip address and port
SOCKET CreateTCPDataSock(u_short port, sockaddr_in& sockAddr, const char* ip)
{
	// create TCP socket
	SOCKET tSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	// error checking
	if(tSocket == -1)
	{
		return tSocket;
	}

	// clear the addr
	ZeroMemory(&sockAddr, sizeof(sockAddr));

	// initialize the address structure
	sockAddr.sin_family = AF_INET; // unsigned short 16 bits
	sockAddr.sin_port = htons( port ); // converts the u_short to network byte order short, 16 bits
	sockAddr.sin_addr.S_un.S_addr = inet_addr( ip ); // converts a c-string to network byte order unsigned long, 32 bits
	// zero 8 bytes

	return tSocket;
}

void ShutDownSocket(SOCKET s)
{
	if(s != INVALID_SOCKET)
	{
		if( shutdown(s, 2) == 0)
		{
			CloseSocket(s);
		}
	}
}