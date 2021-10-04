#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DATA "Half a league, half a league . . ."

/* 
 * This program connects to the socket named in the command 
 * line and sends a one line message to that socket. 
 * The form of the command line is 
 * ustreamwrite pathname
 */
int main(int argc, char *argv[]) {
  if (argc < 2) {
    perror("usage: ustreamwrite pathname");
    exit(1);
  }

  int sock;
  unsigned int length;
  struct sockaddr_un server;

  /* Create socket. */
  sock = socket(AF_UNIX, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("opening stream socket");
    exit(1);
  }

  /* Connect socket using name specified by command line. */
  server.sun_family = AF_UNIX;
  strcpy(server.sun_path, argv[1]);

  length = sizeof(server);  
  if (connect(sock, (struct sockaddr *)&server, length) < 0) {
    close(sock);
    perror("connecting stream socket");
    exit(1);
  }

  if (write(sock, DATA, sizeof(DATA)) < 0) 
    perror("writing on stream socket");

  return 0;
}

