#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

/* 
 * In the included file <sys/un.h> a sockaddr_un is defined 
 * as follows
 * struct sockaddr_un {
 *   short sun_family;
 *   char  sun_path[108];
 * };
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NAME "/home/danil/socket"

/*
 * This program creates a UNIX domain datagram socket, 
 * binds a name to it, 
 * then reads from the socket.
 */
int main(void) {
  int sock, length = sizeof(struct sockaddr_un);
  struct sockaddr_un name;
  char buf[1024];

  /* Create socket from which to read. */
  sock = socket(AF_UNIX, SOCK_DGRAM, 0);
  if (sock < 0) {
    perror("opening datagram socket");
    exit(1);
  }

  /* Create name. */
  name.sun_family = AF_UNIX;
  strcpy(name.sun_path, NAME);
  if (bind(sock, (struct sockaddr *) &name, length) < 0) {
    perror("binding name to datagram socket");
    printf("BIND ERROR: %d\n", errno);

    close(sock);
    exit(1);
  }

  printf("socket -->%s\n", NAME);

  /* Read from the socket */
  if (read(sock, buf, 1024) < 0)
    perror("receiving datagram packet");

  printf("-->%s\n", buf);
  
  close(sock);
  unlink(NAME);

  return 0;
}

