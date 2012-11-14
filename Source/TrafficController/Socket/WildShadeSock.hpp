#ifndef _WILDSHADESOCK_HPP_
#define _WILDSHADESOCK_HPP_

#define WIN32_LEAN_AND_MEAN
#pragma comment(lib, "ws2_32.lib")

// Networking libraries
#ifdef WIN32
	#include <winsock2.h>
	#include <ws2tcpip.h>
#else // UNIX/Linux
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <unistd.h>
	#include <netdb.h>
	#include <apra/inet.h>
#endif

//Libraries platform specific macros
#ifdef WIN32
	extern WSADATA wsaData;
	#define CloseSocket closesocket
	#define GetSocketError  WSAGetLastError
	#define InitWildSock() WSAStartup(WINSOCK_VERSION,&wsaData)
	#define DeInitWildSock() WSACleanup()
	#ifndef socklen_t
		typedef int socklen_t;
	#endif
#else // UNIX/Linux
	#define CloseSocket close
	#define GetSocketError errno
	#define InitWildSock() {}
	#define DeInitWildSock() {}
#endif

// prototypes TCP sockets
SOCKET CreateTCPListeningSock(u_short port);
SOCKET CreateTCPDataSock(u_short port, sockaddr_in& sockAddr, const char* ip);

// general socket functions
void ShutDownSocket(SOCKET s);

#endif