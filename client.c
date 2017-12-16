#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;
  char buffer[BUFFER_SIZE];

  // To handle multiple clients
  // while(1) {
    from_server = client_handshake( &to_server );

    while (1) {
      printf("enter data: \n");
      fgets(buffer, sizeof(buffer), stdin);
      *strchr(buffer, '\n') = 0;
      write(to_server, buffer, sizeof(buffer));
      read(from_server, buffer, sizeof(buffer));
      printf("received [%s]\n", buffer);
    }
  // }
  return 0;
}
