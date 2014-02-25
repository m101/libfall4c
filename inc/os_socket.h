/*
    This file is part of fall4c.

    fall4c is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    fall4c is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with fall4c.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _OS_SOCKET_H
#define _OS_SOCKET_H

#include <errno.h>

// #include "types.h"

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
