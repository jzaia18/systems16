#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  while (1) {
    printf("Client: Please enter some text to send to server $");
    char buf[100];
    fgets(buf, 100, stdin);
    *strchr(buf, '\n') = 0;

    write(to_server, buf, 100);
    printf("Client: Sent!\n");

    read(from_server, buf, 100);

    printf("Client: Received \"%s\" from server\n", buf);
  }
}
