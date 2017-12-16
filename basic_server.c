#include "pipe_networking.h"


int main() {

  int to_client;
  int from_client;
  char buffer[BUFFER_SIZE];

  // to_client has been set within the function
  from_client = server_handshake( &to_client );

  while (read(from_client, buffer, sizeof(buffer))) {
    read(from_client, buffer, sizeof(buffer));
    printf("received: [%s]\n", buffer);
    //process the data somehow
    write(to_client, buffer, sizeof(buffer));
  }
  return 0;
}
