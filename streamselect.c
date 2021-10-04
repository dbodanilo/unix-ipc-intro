#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

/* 
 * This program uses select() to check that someone is 
 * trying to connect before calling accept(). 
 */

int main(void) {
  int sock;
  unsigned int length;
  struct sockaddr_in server;
  int msgsock;
  char buf[1024];
  int rval;
  fd_set ready;
  struct timeval to;

  /* Create socket. */
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("opening stream socket");
    exit(1);
  }
  
  /* Name socket using wildcards. */
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = 0;

  length = sizeof(server);
  if (bind(sock, (struct sockaddr *)&server, length)) {
    perror("binding stream socket");
    exit(1);
  }
  
  /* Find out assigned port number and print it out. */
  if (getsockname(sock, (struct sockaddr *)&server, &length)) {
    perror("getting socket name");
    exit(1);
  }
  printf("Socket has port #%d\n", ntohs(server.sin_port));

  /* Start accepting connections. */
  listen(sock, 5);
  do {
    FD_ZERO(&ready);
    FD_SET(sock, &ready);
    to.tv_sec = 5;
    if (select(sock + 1, &ready, 0, 0, &to) < 0) {
      perror("select");
      continue;
    }
    
    if (FD_ISSET(sock, &ready)) {
      msgsock = accept(sock, (struct sockaddr *)NULL, 
                       (unsigned int *)NULL);
      if (msgsock == -1) 
        perror("accept");
      else do {
        bzero(buf, sizeof(buf));
        if ( (rval = read(msgsock, buf, sizeof(buf))) < 0) 
          perror("reading stream message");
        else if (rval == 0) 
          printf("Ending connection\n");
        else 
          printf("-->%s\n", buf);
      } while (rval > 0);
   
      close(msgsock);
    } else 
        printf("Do something else\n");
  } while (true);

  return 0;
}

