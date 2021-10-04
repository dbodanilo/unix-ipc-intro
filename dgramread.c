#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * In the included file <netinet/in.h> a sockaddr_in is 
 * defined as follows: 
 * struct sockaddr_in {
 *   short sin_family;
 *   u_short sin_port;
 *   struct in_addr sin_addr;
 *   char sin_zero[8];
 * };
 */

/* 
 * This program creates a datagram socket, 
 * binds a name to it, 
 * then reads from the socket.
 */
int main(void) {
  int sock;
  unsigned int length;
  struct sockaddr_in name;
  char buf[1024];

  /* Create a socket from which to read. */
  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock < 0) {
    perror("opening datagram socket");
    exit(1);
  }
  
  /* Create name with wildcards. */
  name.sin_family = AF_INET;
  name.sin_addr.s_addr = INADDR_ANY;
  name.sin_port = 0;

  length = sizeof(name);
  if (bind(sock, (struct sockaddr*)&name, length)) {
    perror("binding datagram socket");
    exit(1);
  }

  /* Find addigned port value and print it out. */
  if (getsockname(sock, (struct sockaddr*)&name, &length)) {
    perror("getting socket name");
    exit(1);
  }
  printf("Socket has port #%d\n", ntohs(name.sin_port));

  /* Read from the socket. */
  if (read(sock, buf, 1024) < 0) 
    perror("receiving datagram packet");

  printf("-->%s\n", buf);

  close(sock);

  return 0;
}

