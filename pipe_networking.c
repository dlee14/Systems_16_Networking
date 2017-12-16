#include "pipe_networking.h"


/*=========================
server_handshake
args: int * to_client
Performs the client side pipe 3 way handshake.
Sets *to_client to the file descriptor to the downstream pipe.
returns the file descriptor for the upstream pipe.
=========================*/
int server_handshake(int *to_client) {
  // int fd;
  int from_client;
  char buffer[HANDSHAKE_BUFFER_SIZE];
  mkfifo("luigi", 0600);

  // Step 1
  printf("[server] handshake: making wkp\n");
  // Blocking on open until someone connects to it
  // When you open a file that already exists, don't need permission
  from_client = open("luigi", O_RDONLY, 0);
  // Blcoking on read until something is there to read
  read(from_client, buffer, sizeof(buffer));
  printf("[server] handshake: received [%s]\n", buffer);
  remove("luigi");
  printf("[server] handshake: removed wkp\n");

  // Step 2
  // Connect to client and send message
  *to_client = open(buffer, O_WRONLY, 0);
  write(*to_client, buffer, sizeof(buffer));

  // Step 3
  read(from_client, buffer, sizeof(buffer));
  printf("[server] handshake received: %s\n", buffer);

  return from_client;
  // char * wkp = "WKP";
  // char * private = "private";
  // int pid;
  // // Making the named pipe
  // if (mkfifo(wkp, 0666)) {
  //   printf("Error: FIFO already exists\n");
  // }
  // fd = open(private, O_WRONLY);
  // printf("Server is reading...");
  // read(fd, &pid, sizeof(pid));
  // remove(wkp);
  //
  // to_client = open(name you got from client)
  // printf("pid read: %d", pid);
  // *to_client = fd;
  // close(fd);
}


/*=========================
client_handshake
args: int * to_server
Performs the client side pipe 3 way handshake.
Sets *to_server to the file descriptor for the upstream pipe.
returns the file descriptor for the downstream pipe.
=========================*/
int client_handshake(int *to_server) {
  int from_server;
  char buffer[HANDSHAKE_BUFFER_SIZE];

  // Send pp pipe to server
  printf("[client] handshake: connecting to wkp\n");
  *to_server = open("luigi", O_WRONLY, 0);

  // Make private pipe, making a unique name by using pid
  sprintf(buffer, "%d", getpid());
  mkfifo(buffer, 0600);

  // Step 1
  write(*to_server, buffer, sizeof(buffer));

  from_server = open(buffer, O_RDONLY, 0);
  read(from_server, buffer, sizeof(buffer));

  remove(buffer);
  printf("[client] handshake: removed pp\n");

  write(*to_server, ACK, sizeof(buffer));

  return from_server;
  // int fd;
  // char * private = "private";
  // char * wkp = "wkp";
  // // Making the named pipe
  // if (mkfifo(private, 0666)) {
  //   printf("Error: FIFO already exists\n");
  // }
  // fd = open(wkp, O_WRONLY, 0666);
  // write(fd, private, sizeof(private);
  // int myfifo = open(private, O_RDONLY, 0666);
  // *to_server = fd;
  // close(fd);
  //
  // return *to_server;
}
