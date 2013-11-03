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

#include <stdlib.h>
#include <stdio.h>

#include <string.h>

#ifdef __linux__
#include <unistd.h>
#include <sys/errno.h>

#include <sys/socket.h>
#include <netdb.h>
#elif defined _WIN32
#include <Ws2tcpip.h>
#endif

#include "sockets_wrap.h"
#include "file.h"
#include "util/debug.h"

#define DEBUG

int xrecv(int sockd, void **buffer, size_t *bufsize, unsigned int flags)
{
  char *filtered_char = "\r\n";
  char *buf, *realbuf;
  int codeno, ready;

  if ( !buffer || !bufsize )
    return -1;

  if ( !*buffer || !*bufsize )
    {
      if (!*buffer)
	free(*buffer);
      *bufsize = BUFFER_SIZE;
      *buffer = calloc( *bufsize, sizeof(char) );
    }

#ifdef DEBUG
  printf("\n== XRECV START ==\n");
#endif
  buf = *buffer;
  realbuf = buf;
  //*
  // Check if data is ready or not to be read
  /* ready = data_read_time_out (sockd, 1, 0);
  ready = ready != 0 && ready != -1;

  if (!ready)
    return -1;
  //*/
  //*/
#ifdef DEBUG
  printf("xrecv: ");
#endif
  do
    {
      codeno = recv(sockd, buf, 1, flags);
      
      if ( codeno == -1 )
	{
	  free (*buffer);
	  *bufsize = BUFFER_SIZE;
	  *buffer = calloc( *bufsize, sizeof(char) );
	  return -1;
	}

      if (  (size_t) (buf - realbuf) >= *bufsize )
	{
	  *bufsize *= 2;
	  realbuf = realloc (realbuf, *bufsize);
	  buf = realbuf + (buf - (char *)*buffer);
	  *buffer = realbuf;
	}
#ifdef DEBUG
      // printf("\\x%x", *buf);
#endif
      buf++;
    }
  while ( codeno && !strstr(realbuf, "\r\n") );

  printf("hexdump\n");
  hexdump(10, realbuf);
  
  // We clean out the bad char
  while ( *filtered_char )
    {
      while ( (buf = strchr(realbuf, *filtered_char)) )
	*buf = '\0';
      filtered_char++;
    }
#ifdef DEBUG
  putchar('\n');
  
  printf("xrecv: '%s'\n", realbuf);
  
  printf("== XRECV END ==\n");
#endif

  codeno = strlen(realbuf);

  return codeno;
}

/*! @brief Send wrapped
 */
int xsend (int sockd, void *msg, size_t msglen, int flags)
{
  int codeno;
  char *realmsg;

  realmsg = msg;

  do
    {
      codeno = send(sockd, msg, 1, flags);
      
      msg++;

      if ( (unsigned int) ((char *)msg - realmsg) >= msglen )
	return -1;
    }
  while ( codeno != 0 || codeno != -1 );

  return 0;
}

/*! @brief Connect to a host
 *  @param rhost
 *  @param service
 *  @param hints
 *  @ret Valid socket descriptor or -1 for error
 */
int connect_rhost (char *rhost, char *service, const struct addrinfo *hints)
{
  struct addrinfo *p, *servinfo;
  int rv, sockfd;

  if ((rv = getaddrinfo(rhost, service, hints, &servinfo)) != 0)
    {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
      exit(1);
    }

  // loop through all the results and connect to the first we can
  for(p = servinfo; p != NULL; p = p->ai_next)
    {
      if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
	{
	  perror("socket");
	  continue;
	}
      if ( (rv = connect(sockfd, p->ai_addr, p->ai_addrlen)) == -1)
	{
	  close(sockfd);
	  perror("connect");
	  continue;
	}
      break; // if we get here, we must have connected successfully
    }
  if ( rv == -1 || sockfd == -1 )
    {
      perror("connect_rhost");
      return -1;
    }

  return sockfd;
}

/*!
 */
int data_read_time_out (int sockd, long sec, long usec)
{
  fd_set rfds;
  struct timeval tv;
  int rv;

  tv.tv_sec = sec;
  tv.tv_usec = usec;

  FD_ZERO(&rfds);
  FD_SET(sockd, &rfds);
  rv = select(sockd+1, &rfds, NULL, NULL, &tv);

  if (rv > 0)
    {
      printf("data_read_time_out: Ready to fetch data\n");
      return rv;
    }
  else
    {
      printf("data_read_time_out: There is no data to fetch\n");
      return -1;
    }
}


unsigned short ip_checksum (unsigned short *data, size_t size)
{
  unsigned long sum;

  if (!data || !size)
    {
      fprintf(stderr, "ip_checksum: Data doesn't exist\n");
      return 0;
    }

  while (size > 1)
    {
      sum += *data++;
      size -= 2;
    }

  if (size > 0)
    sum += *(unsigned char *)data;

  sum = (sum & 0xffff) + (sum >> 16);

  return ~sum;
}
