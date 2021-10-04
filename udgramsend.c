#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DATA "The sea is calm tonight, the tide is full . . ."

/*
 * Here I send a datagram to a receiver whose name I get from 
 * the command line arguments. 
 * The form of the command line is udgramsend pathname
 */

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "usage: %s pathname\n", argv[0]);
    exit(1);
  }

  int sock;
  struct sockaddr name;

  /* Create socket on which to send. */
  sock = socket(AF_UNIX, SOCK_DGRAM, 0); 
  if (sock < 0) {
    perror("opening datagram socket");
    exit(1);
  }

  /* Construct name of socket to send to. */
  name.sa_family = AF_UNIX;
  strcpy(name.sa_data, argv[1]);

  /* Send message. */
  if (sendto(sock, DATA, sizeof(DATA), 0, 
      &name, sizeof(struct sockaddr)) < 0) {
    perror("sending datagram message");
  }
  
  close(sock);

  return 0;
}

