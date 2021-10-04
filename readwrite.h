/*
 * The variable descriptor may be the descriptor of either 
 * a file or of a socket
 */
int cc = read(int descriptor, char *buf, int nbytes);

/*
 * An iovec can include several source buffers
 */
int cc = readv(int descriptor, struct iovec *iov, 
               int iovcnt);

int cc = write(int descriptor, char *buf, int nbytes);

int cc = writev(int descriptor, struct iovec *iovec, 
                int ioveclen);

/* 
 * The variable ``sock'' must be the descriptor of a socket. 
 * Flags may include MSG_OOB and MSG_PEEK. 
 */
int cc = send(int sock, char *msg, int len, int flags);

int cc = sendto(int sock, char *msg, int len, int flags, 
                struct sockaddr *to, int tolen);

int cc = sendmsg(int sock, struct msghdr msg[], int flags);

int cc = recv(int sock, char *buf, int len, int flags);

int cc = recvfrom(int sock, char *buf, int len, int flags, 
                  struct sockaddr *from, int *fromlen);

int cc = recvmsg(int sock, struct msghdr msg[], int flags);

