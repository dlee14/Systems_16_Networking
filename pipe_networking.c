#include "pipe_networking.h"


/*=========================
server_handshake
args: int * to_client
Performs the client side pipe 3 way handshake.
Sets *to_client to the file descriptor to the downstream pipe.
returns the file descriptor for the upstream pipe.
=========================*/
int server_handshake(int *to_client) {
  int fd;
  char * myfifo = "WKP";
  int pid;
  // Making the named pipe
  if (mkfifo(myfifo, 0666)) {
    printf("Error: FIFO already exists\n");
  }
  fd = open(myfifo, O_WRONLY);
  printf("Server is reading...");
  read(fd, &pid, sizeof(pid));
  printf("pid read: %d", pid);
  *to_client = fd;
  close(fd);

  return *to_client;
}


/*=========================
client_handshake
args: int * to_server
Performs the client side pipe 3 way handshake.
Sets *to_server to the file descriptor for the upstream pipe.
returns the file descriptor for the downstream pipe.
=========================*/
int client_handshake(int *to_server) {
  int fd;
  char * myfifo = "private";

  // Making the named pipe
  if (mkfifo(myfifo, 0666)) {
    printf("Error: FIFO already exists\n");
  }
  fd = open(myfifo, O_WRONLY);
  *to_server = fd;
  int pid = getpid();
  write(fd, &pid, sizeof(pid));
  close(fd);

  return *to_server;
}
