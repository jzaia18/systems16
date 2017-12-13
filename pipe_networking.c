#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  char buffer[BUFFER_SIZE];


  open(CLIENTNAME, )

  if (! mkfifo(CLIENTNAME, 0644))
    *to_client = open(CLIENTNAME, O_RDONLY);
  else
    printf("ERROR: %s\n", strerror(errno));

  if (! mkfifo(CLIENTNAME, 0644))
    return open(SERVERNAME, O_RDONLY);
  printf("ERROR: %s\n", strerror(errno));
  return -1;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  return 0;
}
