#include "pipe_networking.h"

#define DEBUGGING 1

/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  char buf[HANDSHAKE_BUFFER_SIZE];


  //Read from client
  if (DEBUGGING) printf("Server: Trying to read from client...\n");
  mkfifo(TO_SERVER_PIPE, 0644);
  int from_client = open(TO_SERVER_PIPE, O_RDONLY);
  read(from_client, buf, HANDSHAKE_BUFFER_SIZE);
  printf("Server: Received \"%s\" from client\n", buf);

  //Write to client
  if (DEBUGGING) printf("Server: Trying to write to client...\n");
  *to_client = open(buf, O_WRONLY);
  strcpy(buf, ACK);
  write(*to_client, buf, HANDSHAKE_BUFFER_SIZE);
  printf("Server: Wrote \"%s\" to client\n", buf);

  if (DEBUGGING) printf("Server: Trying to read from client (again)...\n");
  read(from_client, buf, HANDSHAKE_BUFFER_SIZE);
  if (strcmp(buf, ACK))
    printf("Server: SOMETHING WENT WRONG D:\n");
  else
    printf("Server: Connection established.\n");

  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  char buf[HANDSHAKE_BUFFER_SIZE], server_name[HANDSHAKE_BUFFER_SIZE];

  sprintf(server_name, "%d", getpid());
  strcpy(buf, server_name);
  mkfifo(server_name, 0644);

  if (DEBUGGING) printf("Client: Trying to write PID...\n");
  *to_server = open(TO_SERVER_PIPE, O_WRONLY);
  write(*to_server, buf, HANDSHAKE_BUFFER_SIZE);
  printf("Client: Wrote PID to pipe\n");

  if (DEBUGGING) printf("Client: Trying to read from server...\n");
  int from_server = open(server_name, O_RDONLY);
  read(from_server, buf, HANDSHAKE_BUFFER_SIZE);
  printf("Client: Received \"%s\" from server\n", buf);

  if ( strcmp(buf, ACK))
    printf("Client: SOMETHING WENT WRONG\n");
  else
    printf("Client: Connection established.\n");

  return from_server;
}
