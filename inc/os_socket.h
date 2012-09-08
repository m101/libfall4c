#ifndef _OS_SOCKET_H
#define _OS_SOCKET_H

#include <errno.h>

#include "types.h"

	#ifdef WIN32
        #include <windows.h>
		#include <winsock2.h>
		#include <ws2tcpip.h>
		//#include <wspiapi.h>
		#define sleep(time) Sleep(time)
        #define close(socket) closesocket(socket)

		#define	EAFNOSUPPORT 97	/* Address family not supported by protocol */
		#define INADDRSZ    4
		#define IN6ADDRSZ	16
		int inet_pton(int af, const char *src, void *dst);
	#else
		#include <sys/socket.h>
		#include <netinet/in.h>
		#include <arpa/inet.h>
        #include <sys/wait.h>
	#endif

#endif
