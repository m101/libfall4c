#ifndef SOCKET_WRAP_H_
#define SOCKET_WRAP_H_

#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#define BUFFER_SIZE 256

int xrecv(int sockd, void **buffer, size_t *bufsize, unsigned int flags);
int xsend (int sockd, void *msg, size_t msglen, int flags);
int connect_rhost (char *rhost, char *service, const struct addrinfo *hints);
int data_read_time_out (int sockd, long sec, long usec);
unsigned short ip_checksum (unsigned short *data, size_t size);

#endif /* SOCKET_WRAP_H_ */
