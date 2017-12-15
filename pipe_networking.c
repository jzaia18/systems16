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
  read(from_client, buf, sizeof(buf));
  printf("Server: Received \"%s\" from client\n", buf);

  //Write to client
  if (DEBUGGING) printf("Server: Trying to write to client...\n");
  *to_client = open(buf, O_WRONLY);
  strcpy(buf, ACK);
  write(*to_client, buf, sizeof(buf));
  printf("Server: Wrote \"%s\" to client\n", buf);

  if (DEBUGGING) printf("Server: Trying to read from client (again)...\n");
  read(from_client, buf, sizeof(buf));
  if (strcmp(buf, ACK))
    printf("Server: SOMETHING WENT WRONG D:\n");
  else
    printf("Server: Connection established.\n");

  remove(TO_SERVER_PIPE);

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
  char buf[HANDSHAKE_BUFFER_SIZE], client_name[HANDSHAKE_BUFFER_SIZE];

  // Makes downstream pipe
  sprintf(client_name, "%d", getpid());
  strcpy(buf, client_name);
  mkfifo(client_name, 0644);

  if (DEBUGGING) printf("Client: Trying to write PID...\n");
  *to_server = open(TO_SERVER_PIPE, O_WRONLY);
  write(*to_server, buf, sizeof(buf));
  printf("Client: Wrote PID to pipe\n");

  if (DEBUGGING) printf("Client: Trying to read from server...\n");
  int from_server = open(client_name, O_RDONLY);
  read(from_server, buf, sizeof(buf));
  printf("Client: Received \"%s\" from server\n", buf);

  if (strcmp(buf, ACK))
    printf("Client: SOMETHING WENT WRONG\n");
  else
    printf("Client: Connection established.\n");

  if (DEBUGGING) ("Client: Writing to server (again)\n");
  strcpy(buf, ACK);
  write(*to_server, buf, sizeof(buf));

  remove(client_name);

  return from_server;
}
