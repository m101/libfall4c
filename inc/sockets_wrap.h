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

#ifndef SOCKET_WRAP_H_
#define SOCKET_WRAP_H_

#include <stdlib.h>
#include <sys/types.h>

#ifdef __linux__
#include <sys/socket.h>
#include <netdb.h>
#elif defined _WIN32
#include <Ws2tcpip.h>
#include <io.h>
#define close _close
#endif

#define BUFFER_SIZE 256

int xrecv(int sockd, void **buffer, size_t *bufsize, unsigned int flags);
int xsend (int sockd, void *msg, size_t msglen, int flags);
int connect_rhost (char *rhost, char *service, const struct addrinfo *hints);
int data_read_time_out (int sockd, long sec, long usec);
unsigned short ip_checksum (unsigned short *data, size_t size);

#endif /* SOCKET_WRAP_H_ */
