#include "pipe_networking.h"


int main() {

  int to_client;
  int from_client;

  from_client = server_handshake( &to_client );

  char buf[100];
  read(from_client, buf, 100);

  printf("Server: Received \"%s\" from client, and made 1st letter Q\n", buf);

  buf[0] = 'Q';
  write(to_client, buf, 100);
  printf("Server: Write successful\n");

}
