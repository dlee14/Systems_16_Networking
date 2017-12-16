#include "pipe_networking.h"


int main() {

  int to_client;
  int from_client;
  char buffer[BUFFER_SIZE];

  while (1) {
    from_client = server_handshake( &to_client);
    while(read(from_client, buffer, sizeof(char*))) {
      printf("[server]: Recieved from client: [%s]\n", buffer);
      write(to_client, buffer, sizeof(char*));
    }
  }
}
