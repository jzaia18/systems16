#include "pipe_networking.h"

#ifndef DEBUGGING
#define DEBUGGING 0
#endif


int main() {

  int to_client;
  int from_client;
  char buf[BUFFER_SIZE];

  while (1) {
    from_client = server_handshake( &to_client );

    while(read(from_client, buf, 100)) {

      printf("Server: Received \"%s\" from client, and made 1st letter Q\n", buf);

      buf[0] = 'Q';
      write(to_client, buf, 100);
      if (DEBUGGING) printf("Server: Write successful\n");
    }
  }
}
